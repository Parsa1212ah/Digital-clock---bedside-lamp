/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Digital clock and bedside lamp
Version : v1.0
Date    : 10/06/2021
Author  : 
Company : PaModernShop
Comments: 


Chip type               : ATmega8A
Program type            : Application
AVR Core Clock frequency: 8/000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega8.h>
// I2C Bus functions
#include <i2c.h>
// DS1307 Real Time Clock functions
#include <ds1307.h>
// Declare your global variables here
#include <delay.h>

void main(void)
{
// Declare your local variables here
unsigned char seg[12]={0xc0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80 ,0x90,0xff},h,m,s,i,h1,h2,m1,m2;
// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRC=(1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

// Bit-Banged I2C Bus initialization
// I2C Port: PORTC
// I2C SDA bit: 4
// I2C SCL bit: 5
// Bit Rate: 100 kHz
// Note: I2C settings are specified in the
// Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();

// DS1307 Real Time Clock initialization
// Square wave output on pin SQW/OUT: On
// Square wave frequency: 1Hz

rtc_init(0,1,0);
//rtc_set_time(0,0,0);

// Global enable interrupts
#asm("sei")
i2c_init();
rtc_init(0,1,0);
while (1)
 {  
  rtc_get_time(&h,&m,&s); 
  h1=h/10;
  h2=h%10;
  m1=m/10;
  m2=m%10;
  if(h1==0)h1=10;
 
  if(PIND.0==0){h++;rtc_set_time(h,m,s);while(PIND.0==0);}
  if(PIND.1==0){m++;rtc_set_time(h,m,s);while(PIND.1==0);}
  if(PIND.2==0){s=0;rtc_set_time(h,m,s);}
  
  delay_us(10);    
   
  PORTC.0=1;
  PORTB=seg[h1];
  delay_us(200);
  PORTC.0=0;
  
  PORTB=seg[10]; 
  
  PORTC.1=1;
  PORTB=seg[h2];
  delay_us(200);
  PORTC.1=0;
  
  PORTB=seg[10]; 
  
  PORTC.2=1;
  PORTB=seg[m1];
  delay_us(200);
  PORTC.2=0;
  
  PORTB=seg[10];  

  PORTC.3=1;
  PORTB=seg[m2];
  delay_us(200);
  PORTC.3=0;
  
  PORTB=seg[10]; 
  
  if(h>12){h=0;rtc_set_time(h,m,s);}
  if(m>59){m=0;rtc_set_time(h,m,s);}
  if(PIND.3==0)i++;
  if(i>8)i=0;
  if(i==0)
  {
   PORTD.5=0;
   PORTD.6=0;
   PORTD.7=0;
   while(PIND.3==0);
  }
  if(i==1)
  {
   PORTD.5=1;
   PORTD.6=0;
   PORTD.7=0;
   while(PIND.3==0);
  }
  if(i==2)
  {
   PORTD.5=0;
   PORTD.6=1;
   PORTD.7=0;
   while(PIND.3==0);
  }
  if(i==3)
  {
   PORTD.5=0;
   PORTD.6=0;
   PORTD.7=1;
   while(PIND.3==0);
  }
  if(i==4)
  {
   PORTD.5=1;
   PORTD.6=1;
   PORTD.7=0;
   while(PIND.3==0);
  }
  if(i==5)
  {
   PORTD.5=1;
   PORTD.6=0;
   PORTD.7=1;
   while(PIND.3==0);
  }
  if(i==6)
  {
   PORTD.5=0;
   PORTD.6=1;
   PORTD.7=1;
   while(PIND.3==0);
  }
  if(i==7)
  {
   PORTD.5=1;
   PORTD.6=1;
   PORTD.7=1;
   while(PIND.3==0);
  } 
 }
}
