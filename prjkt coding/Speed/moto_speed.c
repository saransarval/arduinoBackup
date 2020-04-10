#include <16f877a.h>
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_C6,rcv=PIN_C7)
#include "lcd.h"
#fuses Nowdt,hs,NOBROWNOUT,NOLVP

#byte portc=0x07
#byte trisc=0x87

#bit motor=0x07.1

#byte tmr0=0x01

#byte option_reg=0x81
#byte intcon=0x0b

#byte tmr1h=0x0f
#byte tmr1l=0x0e
#byte t1con=0x10
#byte tmr0=0x01

#bit tmr0ie=intcon.5

#bit tmr1on=t1con.0

#zero_ram

int tm=0,sec=0,s[5]={0};
int16 count=0;
int16 t=0,speed=0;
int1 flag=0;
void gsm(unsigned char no);

int myarray[5]={0};

//timer0 interrupt

#INT_TIMER0
timer0()
{
   //speed
   tm++;
   if(tm>=43)
   {
      tm=0;sec++;
      count=make16(tmr1h,tmr1l);
      tmr1on=0;
      tmr1h=0x00;
      tmr1l=0x00;

      flag=1;

      tmr1on=1;
      tmr0=0x00;

   }

}


/////  speed/////
void rpm()
{
         //speed

         /*
         V = C * rpm = Pi * D * rpm
         V = surface tangential velocity
C = circumference of cylinder
D = diameter of cylinder
rpm = rotations per minute
Pi = 3.14 */

         speed=count*3.14;  //
         lcd_command(0x80);
         lcd_data("SPEED: ");
         t=speed;
         t=t/10000;
         s[0]=t/10000;
         lcd_data(t|0x30);

         t=speed;
         t=((t%10000)/1000);
         s[4]=((t%10000)/1000);
         lcd_data(t|0x30);

         t=speed;
         t=((t%1000)/100);
         s[3]=((t%1000)/100);
         lcd_data(t|0x30);

         t=speed;
         t=((t%100)/10);
         s[2]=((t%100)/10);
         lcd_data(t|0x30);

         t=speed;
         t=(t%10);
         s[1]=(t%10);
         lcd_data(t|0x30);
         lcd_data(" km/s");
         

         flag=0;
}

//main program

void main()
{
      trisd=0x00;
      trise=0x00;
      trisc=0x01;

      portd=0x00;
      portc=0x00;
      porte=0x00;

      option_reg=0x87;

      tmr0=0x00;

      t1con=0x07;
      tmr1h=0x00;
      tmr1l=0x00;

      intcon=0x80;
      tmr0ie=1;
      tmr0=0;
      delay_ms(2);
      lcd_inti();
      
      fputs("AT+CMGF=1");
      delay_ms(1000);


fputs("AT+CNMI=1,2,0,0,0");
delay_ms(1000);

fputs("AT+CMGR=1");
delay_ms(1000);


lcd_command(0X80);
lcd_data("MOTOR SPEED......");
lcd_command(0Xc0);
lcd_data("MONITERING SYSTEM   ");

delay_ms(2000);

   lcd_command(0x01);
   delay_ms(5);
   motor=1;

   while(1)
   {
       if(flag==1)
       rpm();
       if(sec==5)
       {
       sec=0;
       gsm(0);

   }
}
}
void gsm(unsigned char no)
{
int b;

sprintf(myarray, "%ld", speed);

if(no==0)
puts("AT+CMGS=\"8122106255\"");

puts("SPEED:");
puts(myarray);
putc(0x1a);
}
