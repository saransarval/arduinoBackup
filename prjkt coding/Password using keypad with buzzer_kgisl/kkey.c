#include<16f877a.h>
#use delay(clock=11059200)
#fuses hs,nowdt

#byte portb=0x06
#byte trisb=0x86
#bit key1=0x06.1
#bit key2=0x06.2
#bit key3=0x06.3
#bit key4=0x06.4

#byte portd=0x08
#byte trisd=0x88

#byte portc=0x07
#byte trisc=0x87
#bit relay1=0x07.1
#bit relay2=0x07.2
#bit buzzer=0x07.3

#byte porte=0x09
#byte trise=0x89

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

#byte intcon=0x0b
#byte option_reg=0x81
#byte tmr0=0x01

unsigned int i=0, a[11]={0,0,0,0,0,0,0,0,0,0,0,},flag=0,tap=0;
int b=0,sec=0,mint=0,help=0,d=0,lcd=0;
int1 lcd_lock=1,buzzer_off=1,top=0;
void display(int n);
void display1(int m);

#INT_TIMER0
TIMER0_isr()
{
b++;
   if(b>=43)
   {
   b=0;
   sec++;
   }
      if(sec>=59)
      {
      sec=0;
      mint++;
      }
         if(mint>=1)
         {
         mint=0;
         tap=1;
         }
}




void command(unsigned char com)
{
portd=com;
reg=0;
rw=0;
en=1;
delay_ms(1);
en=0;
}

void data(unsigned char da)
{
portd=da;
reg=1;
rw=0;
en=1;
delay_ms(1);
en=0;
}

void main()
{
portb=0x00;portd=0x00;portc=0x00;porte=0x00;
trisb=0x1e;trisd=0x00;trisc=0x00;trise=0x00;

option_reg=0x07;
intcon=0xa0;
tmr0=0x00;

command(0x38);
command(0x06);
command(0x0c);
command(0x01);

delay_ms(10);


lcd=0xca;

while(1)
{

if(lcd_lock==1 && top==0)
{
command(0x80);
data("Mint");

command(0x85);
data("Sec");
display(sec);
display1(mint);
command(0x8a);
data("password");
}




   if(!key1)
   {
      delay_ms(300);
      a[i]=1;
      command(lcd);
      data(a[i]|0x30);
      delay_ms(500);
      command(lcd);
      data("*");
      i++;lcd++;
   }

   if(!key2)
   {
      delay_ms(300);
      a[i]=2;
      command(lcd);
      data(a[i]|0x30);
      delay_ms(500);
      command(lcd);
      data("*");
      i++;lcd++;
   }

   if(!key3)
   {
      delay_ms(300);
      a[i]=3;
      command(lcd);
      data(a[i]|0x30);
      delay_ms(500);
      command(lcd);
      data("*");
      i++;lcd++;
   }

   if(!key4)
   {
      delay_ms(300);
      a[i]=4;
      command(lcd);
      data(a[i]|0x30);
      delay_ms(500);
      command(lcd);
      data("*");
      i++;lcd++;
   }

   if(i>=4)
   {
      i=0;
      flag=1;
   }

      if(a[0]==1 && a[1]==2 && a[2]==3 && a[3]==4 && (flag==1))
      {
         command(0x01);
         command(0x80);
         data("Password Match");
         lcd_lock=0;
        // command(0xc0);
        // data(a[0]|0x30);
        // data(a[1]|0x30);
        // data(a[2]|0x30);
        // data(a[3]|0x30);
         //command(0xc6);
         //data("**");
         //command(0xc0);
         //data("**");
         d=1;
         flag=0;
         buzzer_off=1;
         relay1=1;
         relay2=1;
         delay_ms(250);
         a[0]=0; a[1]=0; a[2]=0; a[3]=0;sec=0;mint=0,tap=0;

      }

      if(tap==1  && lcd_lock==1 || flag==1)
      { 
         d=0;top=1;
         flag=0;
         buzzer=1;
         tap=0;

         command(0xc0);
         data("********");
         relay1=0;
         relay2=0;
         command(0x80);
         data("Password Error  ");
      }

}

}


void display(int n)
{
int j=0,z[2];
for(j=0;j<=1;j++)
{
z[j]=n%10;
n=n/10;
}
d=0;
command(0xc6);
data(z[1]|0x30);
data(z[0]|0x30);
}
void display1(int m)
{
int j=0,z[2];
for(j=0;j<=1;j++)
{
z[j]=m%10;
m=m/10;
}
d=0;
command(0xc0);
data(z[1]|0x30);
data(z[0]|0x30);
}
