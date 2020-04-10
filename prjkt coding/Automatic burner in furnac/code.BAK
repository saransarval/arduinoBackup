#include<16f877a.h>
#use delay(clock=11059200)
#fuses NOWDT,HS, PUT, NOPROTECT,NOBROWNOUT, NOLVP, NOCPD, NOWRT

#byte trisb=0x86
#byte portb=0x06

#byte trisd=0x88
#byte portd=0x08

#byte trisc=0x87
#byte portc=0x07

#byte trise=0x89
#byte porte=0x09

#byte tmr0=0x01
#byte intcon=0x0b
#byte option_reg=0x81

#bit reg=porte.0
#bit rw=porte.1
#bit en=porte.2

#bit key1=portb.0
#bit key2=portb.1
#bit key3=portb.2
#bit IR=portb.3

#bit tmr0ie=intcon.5

#bit RELAY=portc.0
#bit LED=portc.1

int b=0,sec=0,mint=0,hours=0;
void display_sec(unsigned int s);
void display_mint(unsigned int m);
void display_hours(unsigned int h); 

#int_timer0
timer0_isr()
{
b++;
   if(b>=43)
   {
      b=0;
      sec++;
         if(sec>=60)
         {
            sec=0;
            mint++;
             }
              if(mint>=60)
                  {
                     mint=0;
                     hours++;
                       }
                        if(hours>=12)
                          {
                              hours=0;
                               }
    }
}


void command(unsigned int com)
{
      portd=com;
      reg=0;
      rw=0;
      en=1;
      delay_ms(1);
      en=0;
}
void data(unsigned int dat)
{
      portd=dat;
      reg=1;
      rw=0;
      en=1;
      delay_ms(1);
      en=0;
}

void main()
{

      trisb=0x0f;
      portb=0x00;

      trisd=0x00;
      portd=0x00;

      trisc=0x00;
      portc=0x00;

      trise=0x00;
      porte=0x00;
      
      intcon=0xc0;
      option_reg=0x07;
      tmr0=0x00;
      tmr0ie=0;
      
      command(0x38);
      command(0x0c);
      command(0x06);
      delay_ms(100);
      
      command(0x80);
      data("AUTOMATIC BURNER");
      command(0xc0);
      data("   SYSTEM   ");
      delay_ms(2000);
      command(0x01);
      
while(1)
{
      command(0x80);
      data("T_H:M:S:");
      display_sec(sec);
      display_mint(mint);
      display_hours(hours); 

         if(key1==0)
          {
            tmr0ie=1;
            RELAY=1;
         
          }
         if(IR==1)
         { 
         if((sec>=45) && (key3==0))
         {
           RELAY=0;
           LED=1;
           command(0xc0);
           data("BURNING PROCESS"); 
         } 
         }
}
}
      
void display_sec(unsigned int s)
{
int c,i[2];

      for(c=0;c<2;c++)
      {
         i[c]=s%10;
         s=s/10;
      }
         command(0x8e);
         data(i[1]|0x30);
         data(i[0]|0x30);
         delay_ms(200);
}
void display_mint(unsigned int m)
{
int c,j[2];

      for(c=0;c<2;c++)
      {
         j[c]=m%10;
         m=m/10;
      }
         command(0x8b);
         data(j[1]|0x30);
         data(j[0]|0x30);
         data(":");
         delay_ms(200);
}
void display_hours(unsigned int h)
{
int c,k[2];

      for(c=0;c<2;c++)
      {
         k[c]=h%10;
         h=h/10;
      }
         command(0x88);
         data(k[1]|0x30);
         data(k[0]|0x30);
         data(":");
         delay_ms(200);
}      
      
