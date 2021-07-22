#include "i2c.h"
/*
void I2C_Initialize(const unsigned long feq_K) //Begin IIC as master
{
  TRISC3 = 0;  TRISC4 = 0;  //Set SDA and SCL pins as input pins
  
  SSPCON  = 0b00101000;    //pg84/234 
  SSPCON2 = 0b00000000;    //pg85/234
  
  SSPADD = (_XTAL_FREQ/(4*feq_K*100))-1; //Setting Clock Speed pg99/234
  SSPSTAT = 0b00000000;    //pg83/234
}

void I2C_Hold()
{
    while (   (SSPCON2 & 0b00011111)    ||    (SSPSTAT & 0b00000100)   ) ; //check the bis on registers to make sure the IIC is not in progress
}

void I2C_Begin()
{
  I2C_Hold();  //Hold the program is I2C is busy  
  SEN = 1;     //Begin IIC pg85/234
}



void I2C_End()
{
  I2C_Hold(); //Hold the program is I2C is busy  
  PEN = 1;    //End IIC pg85/234
}

void I2C_Write(unsigned data)
{
  I2C_Hold(); //Hold the program is I2C is busy 
  SSPBUF = data;         //pg82/234
}

unsigned short I2C_Read(unsigned short ack)
{
  unsigned short incoming;
  I2C_Hold();
  RCEN = 1;
  
  I2C_Hold();
  incoming = SSPBUF;      //get the data saved in SSPBUF
  
  I2C_Hold();
  ACKDT = (ack)?0:1;    //check if ack bit received  
  ACKEN = 1;          //pg 85/234
  
  return incoming;
}
void Write_Byte_To_24LC64_EEPROM(unsigned int Address, unsigned char DataByte)
{
    I2C_Begin();                    // Start i2c communication
    // Send i2c address of 24LC64 with write command
    I2C_Write(Address>>8);              // Write Address upper byte
    I2C_Write((unsigned char)Address);        // Write Address lower byte
    I2C_Write(DataByte);              // Write data byte
    I2C_End();                      // Stop i2c communication
}
*/

#include "i2c.h"

 







void i2c_init(void)

{

  TIDAT=0;

  ICLK=1;

  IDAT=1;

}



void i2c_start(void)

{

  ICLK=1;

  IDAT=1;

__delay_ms(10);
  IDAT=0;

__delay_ms(10);

}



void i2c_stop(void)

{

  ICLK=1;

  IDAT=0;

__delay_ms(10);

  IDAT=1;

__delay_ms(10);

}



void i2c_wb(unsigned char val)

{

  unsigned char i;

  ICLK=0;

  for(i=0;i<8;i++)

  {

    IDAT=((val>>(7-i))& 0x01);

    ICLK=1;

__delay_ms(10);

    ICLK=0;

  }	

  IDAT=1;

__delay_ms(10);

  ICLK=1;

__delay_ms(10);

  ICLK=0;

}



unsigned char i2c_rb(unsigned char ack)

{

  char i;

  unsigned char ret=0;



  ICLK=0;

  TIDAT=1;

  IDAT=1;

  for(i=0;i<8;i++)

  {

    ICLK=1;

__delay_ms(10);

    ret|=(IDAT<<(7-i));

    ICLK=0;

  }

  TIDAT=0;

  if(ack)

    IDAT=0;

  else

	IDAT=1;

__delay_ms(10);

  ICLK=1;

__delay_ms(10);

  ICLK=0;



  return ret;

}