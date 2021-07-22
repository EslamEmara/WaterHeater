/*
 * File:   main.c
 * Author: Eslam
 *
 * Created on July 4, 2020, 2:18 PM
 */

#include "UTILS.h"
#include "gpio.h"
#include "adc.h"
#include "lcd.h"
#include "SEG.h"
#include "timer0.h"
#include "eeprom_i2c.h"
#include "heater_fan.h"
#include "ExtInt.h"
#include <xc.h>

#define _XTAL_FREQ              20000000             //20MHz clock

#define UP                      4                    //interrupt on change pins
#define DOWN                    5
#define LED                     3

#define TEMP_ADRESS             0x20                 //TEMPRATURE ADDRESS IN EEPROM  

//FUNCTIONS PROTOTYPES
float get_temp(void);                               
void display_temp(u8* temp);
void adjust_temp(void);
void startup(void);
u8 get_start_temp (void);
void LED_display(void);
void adjust_temp_periodic (void);
float get_avg_temp (void);
void show_instructions(void);
void __interrupt () ISR(void);

//Global variables
u8 set_temp;                            
u8 timer0_count;
u16 led_count;
u16 settingoff_count;
 // flags declaration 
struct flags                           
{
     u8 on_pressed      :1 ;                        //SYSTEM ON/OFF
     u8 settings_mode   :1 ;                        //SETTINGS 
     u8 startup_done    :1 ;                        //STARTUP MESSAGE
     u8 displayed       :1 ;
} flag;

void main(void) {
    //VARIABLES INTIALLIZATION 
    flag.on_pressed=0;                          
    flag.settings_mode=0;
    flag.startup_done=0;
    flag.displayed = 0;

    timer0_count=0;
    timer0_count16=0;
    led_count = 0;
    settingoff_count=0;
    
    //SET PINS DIRECTION
    GPIO_SetPinDir(&PORTB,LED,MODE_OUT);                   //HEATER LED
    GPIO_ClrPin(&PORTB,LED);                              //INITALIZE HEATER LED 
   
    //PERIFIRALS INITIALIZATIONS 
    Lcd_init();
    SEG_init();
    ADC_init();
    ADC_SetFreq(2);
    heater_fan_init();
    timer0_init(PRE32,1);
    ExtInt_init();
    I2C_Master_Init(1000000);
    
    set_temp = get_start_temp();            // INITIALIZE SET TEMP FROM EEPROM

    //PROGRAM
    while (1)
    {    
        if (flag.on_pressed == 0)                    //MODE OFF
        {
            fan_mode(OFF);                           //FAN OFF
            heater_mode(OFF);                       //HEATER OFF  
            Lcd_Clear();  
        }
        else                                         // MODE ON
        {     
            if (flag.startup_done == 0)
            {
                startup();                       //STARTUP SHOWN AT FIRST
            }
            else 
            {
                adjust_temp_periodic();
                if(settingoff_count <= 5000)
                {
                    Lcd_Clear();
                    SEG_blink(set_temp);                        //BLINK SET TEMP EVERY 1 S FOR 5S
                    EEPROM_Write(TEMP_ADRESS,set_temp);        // SAVE NEW VALUE IN EEPROM
                    flag.displayed = 0;
                }
                else 
                {
                    if (flag.displayed == 0)
                    {
                        show_instructions();
                        flag.displayed = 1;
                    }
                    SEG_display((u8)(get_temp())); // SHOW ACTUAL TEMP AFTER 5 S
                    flag.settings_mode = 0;
                }
            }
        }
    }
    return;
}
void __interrupt() ISR(void)                
{  
    u8 false_read_PORTB = PORTB;                    // READ PORTB AS DATASHEET 
        
    if (RBIF == 1)                                  // INTERRUPT ON CHANGE PINS
    {   
        if(flag.on_pressed == 1)                            // ON MODE
        {   
            if ((GPIO_GetPin(&PORTB,UP))&& set_temp < 75 && flag.settings_mode == 1)      //CHECK FOR PRESSED BUTTON AND MODE     
             {
                set_temp += 5;                      //TEMP_UP                           
             }
            else if ((GPIO_GetPin(&PORTB,DOWN)) && set_temp > 35 && flag.settings_mode == 1)
             {
                set_temp -= 5;                      //TEMP_DOWN
             }
            flag.settings_mode =1;                    //SETTINGS MODE ON
            settingoff_count=0;                 
        }
        else 
        {
            
        }
        
        RBIF = 0;                                       //CLEAR INT FLAG

    }
    else if (INTF)                                          // RB0 INT
    { 
        flag.on_pressed ^= 1;                         // ON / OFF
        flag.settings_mode = 0;                       //SETTINGS OFF
        flag.startup_done = 0;                       //SHOW WELCOME WHEN START
        INTF = 0;                                    //CLEAR INT FLAG
    }
    if(TMR0IF)                                       // TIMER0 OVERFLOW 
    { 
        TMR0 = 110;     
        timer0_count++;                         //8BIT VARIABLE INCREMENT
        timer0_count16++;                       //16BIT VARIABLE INCREMENT
        led_count++;                            //LED BLINK VARIABLE
        settingoff_count++;                     //SETTINGS MODE BLINK
        TMR0IF=0;                               // CLEAR TIMER INT FLAG
    } 
}
void startup (void)                             //WELCOME MESSAGE
{
    Lcd_Print_String("Heater ON");
    __delay_ms(500);
    Lcd_Clear();
    show_instructions();
    while (1)                                   // WAIT FOR BUTTON PRESS
    {   if (flag.on_pressed)
        {
            adjust_temp_periodic(); 
           SEG_display ((u8)get_temp());           // DISPLAY 7SEGS CURRENT TEMP
            if (flag.settings_mode == 1)
             {
              Lcd_Clear(); 
              flag.startup_done = 1;
              break; 
             }
        }
        else 
           break;
    }
}
float get_temp(void)                            // GET VALUE OF TEMPRATURE CHANNEL
{ 
    u16  adc = ADC_Read(CH2);                   // Reading ADC values
    return ((adc*((float)5000/1024))/10) ;      // Convert it into temperature 
}
void adjust_temp(void)                          
{
    float avg_temp =  get_avg_temp ();
    if (avg_temp <= set_temp -5)                    // ADJUST TEMP TO SET TEMP
    {
        heater_mode (ON);                            // HEATER ON
        fan_mode(OFF);                               // FAN OFF
    }
    else if (avg_temp >= set_temp +5)
    {
        heater_mode(OFF);                             //HEATER OFF
        fan_mode(ON);                                // FAN ON 
    }
    LED_display();
}
u8 get_start_temp (void)
{   
        //Read set temperature from ext eeprom if set 
    u8 tmp = EEPROM_Read(TEMP_ADRESS);
    if (tmp >= 35 && tmp <= 75)
        return tmp;
    else 
        return 60;
}
void LED_display(void)
{
      if (GPIO_GetPin(&PORTC,2))                      //READ HEATER PIN
    {
         if (led_count >= 500)
        {
            TOGGLEBIT(PORTB,LED);                     // IF HEATER ON BLINK
            led_count = 0;
        } 
    }
    else 
        GPIO_SetPin(&PORTB,3);                     // IF HEATER OFF SET THE PIN 
}
float get_avg_temp (void)
{
    float avg_temp = 0;
    for(int i = 0 ; i< 10 ; i++)          // GET THE AVERAGE OF LAST 10 READINGS
    {
        avg_temp += get_temp();                 
    }
    avg_temp /= 10;    
    return avg_temp;
}
void adjust_temp_periodic (void)
{ 
    if (timer0_count >= 100)                 // CHECK FOR TEMP EVERY 100 MS
     {
        adjust_temp();                  
        timer0_count=0;                      //RESET COUNTER
     }
}
void show_instructions (void)
{
    Lcd_Print_String("Press RB4 / RB5");
    Lcd_Set_Cursor(2,1);
    Lcd_Print_String("to adjust");

}