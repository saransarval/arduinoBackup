#include <16F877A.h>
#device adc=10
#use delay(clock=11059200)
#fuses NOWDT,HS, PUT, NOPROTECT,NOBROWNOUT, NOLVP, NOCPD, NOWRT

#byte porta=0x05
#byte trisa=0x85

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
#byte rcreg=0x1a

#byte adcon0=0x1f
#byte adcon1=0x9f

#byte adresh=0x1e
#byte adresl=0x9e
#byte pir1=0x0c

#bit go=0x1f.2

#bit tmr0ie=intcon.5
#bit rbie=intcon.3

#bit reg=porte.0
#bit rw=porte.1
#bit en=porte.2

#bit key1=portb.1
#bit key2=portb.2
#bit key3=portb.3
#bit s1=portb.4
#bit s2=portb.5
#bit s3=portb.6
#bit s4=portb.7

#bit relay1=portc.0

#define VOLTAGE 820

int1 flag=0 , battery_1_flag = 0 , battery_2_flag = 0, relay1_flag=0;
void display_sec(unsigned int s);
void display_mint(unsigned int m);
void display_hours(unsigned int h);
void display_enter_sec(unsigned int s);
void display_enter_mint(unsigned int m);
void display_enter_hours(unsigned int h);
void display(unsigned int16 n);
int b=0,sec=0,mint=0,hours=0 , enter_sec=0, enter_mint=0, enter_hours=0, enter_sec_1=0, enter_mint_1=0, enter_hours_1=0,x=1,y=1;
unsigned int16  Battery_1 = 0;

#int_rb
rb_isr()
{
   if(s1==0)
   {
      enter_sec++;
      }
         if(s2==0)
         {
            enter_mint++;
            }
               if(s3==0)
               {
                  enter_hours++;
                  }
                        if(s4==0)
                        {
                           flag=1;

                           }
}

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
      porta=0x00;
      trisa=0x01;

      trisb=0xfe;
      portb=0x00;

      trisd=0x00;
      portd=0x00;

      trisc=0x00;
      portc=0x00;

      trise=0x00;
      porte=0x00;

      intcon=0xc8;
      option_reg=0x07;
      tmr0=0x00;

      adresh=0x00;
      adresl=0x00;
      adcon1=0x82;
      adcon0=0x81;

      command(0x38);
      command(0x0c);
      command(0x06);
      command(0x01);

      delay_ms(1);
      command(0x80);
      data("   BATTERY  ");
      command(0xc0);
      data("   SELETION    ");
      delay_ms(1000);
      command(0x01);
      delay_ms(100);

      command(0x80);
      data("TIME M-KEY.1");
      command(0xc0);
      data("CAPACITY M-KEY.2");
      delay_ms(100);

while(1)
{
      delay_ms(10);
      go=1;
      while(go==1);
      Battery_1=make16(adresh,adresl);
      Battery_1=(Battery_1/5);
      delay_ms(10);

if((key1==0) && (x==1))
{
      battery_1_flag = 1;
      command(0x01);
      delay_ms(2);
}
if(battery_1_flag==1)
{
      x = 0;
      command(0x80);
      data("H:M:S::");
      display_sec(sec);
      display_mint(mint);
      display_hours(hours);
      command(0xc0);
      data("H:M:S::");
      display_enter_sec(enter_sec);
      display_enter_mint(enter_mint);
      display_enter_hours(enter_hours);
      delay_ms(100);

      rbie = 1;
}
if(flag==0)
{
      if((enter_sec==60) || (enter_mint==60) || (enter_hours==12))
         {
            if(enter_sec==60)
               {
                  enter_sec=0;
                   }
                  if(enter_mint==60)
                     {
                        enter_mint=0;
                          }
                        if(enter_hours==12)
                           {
                              enter_hours=0;
                                }
         }
}
if(flag==1)
{
      tmr0ie=1;
      relay1=1;
      relay1_flag=1;
}
if((sec==enter_sec) && (mint==enter_mint) && (hours==enter_hours) && (relay1_flag==1))
{
      relay1_flag=0;
      flag=0;
      enter_sec=0;
      enter_mint=0;
      enter_hours=0;
      sec=0;mint=0;
      hours=0;
      tmr0ie=0;
      battery_1_flag=0;
      rbie = 0;
      command(0x01);
      command(0x80);
      data("BAT_1:");
      display(Battery_1);

      if(Battery_1<=204)
      {
      relay1=0;
      command(0xc0);
      data("BAT_1:1V CHARGED");
      }
      else if(Battery_1<=408)
      {
      relay1=0;
      command(0xc0);
      data("BAT_1:2V CHARGED");
      }
      else if(Battery_1<=612)
      {
      relay1=0;
      command(0xc0);
      data("BAT_1:3V CHARGED");
      }
      else if(Battery_1<=816)
      {
      relay1=0;
      command(0xc0);
      data("BAT_1:4V CHARGED");
      }
      else if(Battery_1<=1020)
      {
      relay1=0;
      command(0xc0);
      data("BAT_1:5V CHARGED");
      }
}
if((key2==0) && (y==1))
{
      battery_2_flag=1;
}
if(battery_2_flag==1)
{
      relay1=1;
      y=0;
      command(0x01);
      command(0x80);
      data("CAPACITY MONITOR");
      command(0xc0);
      data("BAT_1 CHARGING");
      delay_ms(500);
}
if(Battery_1>=VOLTAGE)
{
      relay1=0;
      battery_2_flag=0;
      command(0x01);
      command(0x80);
      data("BAT_1:");
      display(Battery_1);

      if(Battery_1<=204)
      {
      command(0xc0);
      data("BAT_1:1V CHARGED");
      }
      else if(Battery_1<=408)
      {
      command(0xc0);
      data("BAT_1:2V CHARGED");
      }
      else if(Battery_1<=612)
      {
      command(0xc0);
      data("BAT_1:3V CHARGED");
      }
      else if(Battery_1<=816)
      {
      command(0xc0);
      data("BAT_1:4V CHARGED");
      }
      else if(Battery_1<=1020)
      {
      command(0xc0);
      data("BAT_1:5V CHARGED");
      }
      delay_ms(500);
}
if(key3==0)
{
      relay1=0;
      battery_2_flag=0;
      command(0x01);
      command(0x80);
      data("BAT_1:");
      display(Battery_1);
      
      if(Battery_1<=204)
      {
      command(0xc0);
      data("BAT_1:1V CHARGED");
      }
      else if(Battery_1<=408)
      {
      command(0xc0);
      data("BAT_1:2V CHARGED");
      }
      else if(Battery_1<=612)
      {
      command(0xc0);
      data("BAT_1:3V CHARGED");
      }
      else if(Battery_1<=816)
      {
      command(0xc0);
      data("BAT_1:4V CHARGED");
      }
      else if(Battery_1<=1020)
      {
      command(0xc0);
      data("BAT_1:5V CHARGED");
      }
      delay_ms(500);
}
}
}

void display(unsigned int16 n)
{
   int i = 0;
   int a[4];

      for(i=0;i<=3;i++)
      {
         a[i]=n%10;
         n=n/10;
      }

         data(a[3]|0x30);
         data(a[2]|0x30);
         data(a[1]|0x30);
         data(a[0]|0x30);
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
void display_enter_sec(unsigned int s)
{
int c,i[2];

      for(c=0;c<2;c++)
      {
         i[c]=s%10;
         s=s/10;
      }
         command(0xce);
         data(i[1]|0x30);
         data(i[0]|0x30);
         delay_ms(200);
}
void display_enter_mint(unsigned int m)
{
int c,j[2];

      for(c=0;c<2;c++)
      {
         j[c]=m%10;
         m=m/10;
      }
         command(0xcb);
         data(j[1]|0x30);
         data(j[0]|0x30);
         data(":");
         delay_ms(200);
}
void display_enter_hours(unsigned int h)
{
int c,k[2];

      for(c=0;c<2;c++)
      {
         k[c]=h%10;
         h=h/10;
      }
         command(0xc8);
         data(k[1]|0x30);
         data(k[0]|0x30);
         data(":");
         delay_ms(200);
}


