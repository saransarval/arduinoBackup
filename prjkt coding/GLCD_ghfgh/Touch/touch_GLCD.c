#include <16F877A.h>
#device adc=10
#use delay(clock=11059200)

#byte trisa=0x85
#byte porta=0x05

#byte trisd=0x88
#byte portd=0x08

#byte trise=0x89
#byte porte=0x09


#byte adcon0=0x1f
#byte adcon1=0x9f
#byte adresh=0x1e
#byte adresl=0x9e

#bit GO=0x1f.2

#bit reg=porte.0
#bit rw=porte.1
#bit en=porte.2


#bit TOUCH_X1= porta.0
#bit TOUCH_X2= porta.2

#bit TOUCH_Y1= porta.1
#bit TOUCH_Y2 =porta.5
void command(unsigned int);

void data(unsigned int);

#include "Header_Touch.h"

unsigned int resolution;



//int16 adc_value1=0, adc_value2=0;

void display1(int16);
void display2(int16);

void command(unsigned int com)
{
   reg=0;
   rw=0;
   portd=com;
   en=1;
   delay_ms(1);
   en=0;
}

void data(unsigned int dat)
{
   reg=1;
   rw=0;
   portd=dat;
   en=1;
   delay_ms(1);
   en=0;
}



void main()
{

   porta=0x00;
   
   trisd=0x00;
   portd=0x00;
   
   trise=0x00;
   porte=0x00;
   
   ADRESH=0x00;
   ADRESL=0x00;

   
   command(0x38);
   command(0x0c);
   command(0x06);
   command(0x01);
   delay_ms(2);
   
   command(0x80);
   data("  TOUCH SCREEN  ");
   command(0xc0);
   data("     SYSTEM     ");
   delay_ms(500);
   command(0x01);
   delay_ms(2);

   while(1)
   {
     
     Resolution=read_touch();
     
     command(0x80);
     data((Resolution/10)|0x30);
     data((Resolution%10)|0x30);
     /* adresh=0x00;
      adresl=0x00;
      
      trisa=0x05;
      Y1=0; Y2=1;  

      adcon0=0x81;
      adcon1=0x42;
      delay_ms(10);
      GO=1; 
      while(GO==1); 
      adc_value1=make16(ADRESH,ADRESL);        
      
      display1(adc_value1);
      
      delay_ms(500);
      
      /////////////////////////////////
      
      adresh=0x00;
      adresl=0x00;
      
      trisa=0x22;
      X1=0; X2=1;
      
 
      adcon0=0x89;
      adcon1=0x42;
      delay_ms(10);
      GO=1;
      while(GO==1);
      adc_value2=make16(ADRESH,ADRESL);          
      
      display2(adc_value2);
      
      delay_ms(500);*/
      
   }
}

void display1(int16 val)
{
   int8 a[4],i;
   for(i=0;i<4;i++)
   {
      a[i]=val%10;
      val=val/10;
   }
  
   command(0x80);
   data("X:");
   data(a[3]|0x30);
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
   delay_ms(10);
   }
   
void display2(int16 val)
{
   int8 a[4],i;
   for(i=0;i<4;i++)
   {
      a[i]=val%10;
      val=val/10;
   }
  
   command(0xc0);
   data("Y:");
   data(a[3]|0x30);
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
   delay_ms(10);
   }   



