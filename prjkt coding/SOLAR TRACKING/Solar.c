#include <16F877A.h>
#device adc=10
#use delay(clock=11059200)
#fuses NOWDT,HS,PUT, NOPROTECT,BROWNOUT, NOLVP, NOCPD, NOWRT

#byte porta=0x05
#byte trisa=0x85

#byte portb=0x06
#byte trisb=0x86

#byte portc=0x07
#byte trisc=0x87

#byte portd=0x08
#byte trisd=0x88

#byte porte=0x09
#byte trise=0x89

#byte option_reg=0x81
#byte intcon=0x0b
#byte tmr0=0x01
#byte pir1=0x0c

#byte adcon0=0x1f
#byte adcon1=0x9f

#byte adresh=0x1e
#byte adresl=0x9e

#bit go=0x1f.2

#bit relay1=portb.4
#bit relay2=portb.5

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

#bit LEFT=portb.0
#bit RIGHT=portb.1

unsigned int16 LDR1=0, LDR2=0, LDR3=0, LDR4=0, battery_1=0, battery_2=0, lock=0, lock1=1, lock2=1, lock3=1, lock4=1;
int b=0;
int1 flag=0,flag_1=0,flag_2=0,flag_3=0,flag_4=0,d=0,a=0,c=0;

void display1(unsigned int16);
void display2(unsigned int16);

void display3(unsigned int16);
void display4(unsigned int16);

/*void display5(unsigned int16);
void display6(unsigned int16);*/

void command(unsigned char com);
void data(unsigned char da);

#int_timer0
timer0_isr()
{
command(0x80);
data("GRT");
b++;
if(b==43)
{
b=0;
flag=1;
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
   trisa=0x3f;
   porta=0x00;
   portb=0x00;
   trisb=0x00;
   trisd=0x00;
   portd=0x00;
   trise=0x00;
   porte=0x00;
   trisc=0x00;
   portc=0x00;

   intcon=0xc0;
   option_reg=0x07;
   tmr0=0x00;

   adresh=0x00;
   adresl=0x00;
   adcon1=0x82;

   command(0x38);
   command(0x06);
   command(0x0c);
   command(0x01);

   command(0x80);
   data("SOLAR TRACKING");

   /*set_timer0(0x00); //set TMR0 initial value to zero
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); //set timer0 mode

   enable_interrupts(INT_TIMER0); //enable timer overflow interrupt

   enable_interrupts(GLOBAL); //enable global interrupt


   setup_adc( ADC_CLOCK_INTERNAL );
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4_AN5);*/

   delay_ms(2000);
   command(0x01);
   delay_ms(2);


   while(1)
   {

      delay_ms(100);
      adcon0=0x81;
      go=1;
      while(go==1);
      LDR1=make16(adresh,adresl);
      delay_ms(10);
      display1(LDR1);

      delay_ms(100);
      adcon0=0x89;
      go=1;
      while(go==1);
      LDR2=make16(adresh,adresl);
      delay_ms(10);
      display2(LDR2);

      delay_ms(100);
      adcon0=0x91;
      go=1;
      while(go==1);
      LDR3=make16(adresh,adresl);
      delay_ms(10);
      display3(LDR3);

      delay_ms(100);
      adcon0=0x99;
      go=1;
      while(go==1);
      LDR4=make16(adresh,adresl);
      delay_ms(10);
      display4(LDR4);

      /*delay_ms(100);
      adcon0=0xa1;
      go=1;
      while(go==1);
      battery_1=make16(adresh,adresl);
      delay_ms(10);
      display5(battery_1);

      delay_ms(100);
      adcon0=0xa9;
      go=1;
      while(go==1);
      battery_2=make16(adresh,adresl);
      delay_ms(10);
      display6(battery_2);*/

      /*set_adc_channel(0);
      delay_us(100);         //wait for the acquisition time
      value1=read_adc();
      delay_us(4);
      display1(value1);

      set_adc_channel(1);
      delay_us(100);         //wait for the acquisition time
      value2=read_adc();
      delay_us(4);
      display2(value2);

      set_adc_channel(3);
      delay_us(100);         //wait for the acquisition time
      value3=read_adc();
      delay_us(4);
      display3(value3);

      set_adc_channel(4);
      delay_us(100);         //wait for the acquisition time
      value4=read_adc();
      delay_us(4);
      display4(value4);

      set_adc_channel(5);
      delay_us(100);         //battery_1 status
      battery_1=read_adc();
      delay_us(4);
      display4(battery_1);

      set_adc_channel(6);
      delay_us(100);         //battery_2 status
      battery_2=read_adc();
      delay_us(4);
      display4(battery_2);*/

        if((LDR1>LDR2) && (LDR1>LDR3) && (LDR1>LDR4) && (flag_1==0))
        {
         flag_1=1;
        }
        if((flag_1==1) && (lock1==1))
        {
         a=1;
         flag_1=0;
         RIGHT=1;
         LEFT=0;
         lock1=0;
         delay_ms(1250);
         RIGHT=0;
        }

        if((LDR2>LDR1) && (LDR2>LDR3) && (LDR2>LDR4) && (flag_2==0))
        {
         flag_2=1;
        }
        if((flag_2==1) && (lock2==1))
        {
         a=0;
         flag_2=0;
         RIGHT=1;
         lock2=0;
         LEFT=0;
         delay_ms(1250);
         RIGHT=0;
        }

        if((LDR3>LDR1) && (LDR3>LDR2) && (LDR3>LDR4) && (flag_3==0))
        {
         flag_3=1;
        }
        if((flag_3==1) && (lock3==1))
        {
         c=1;
         flag_3=0;
         RIGHT=1;
         lock3=0;
         LEFT=0;
         delay_ms(1250);
         RIGHT=0;
        }

        if((LDR4>LDR1) && (LDR4>LDR2) && (LDR4>LDR3) && (flag_4==0))
        {
         flag_4=1;
        }
        if((flag_4==1) && (lock4==1))
        {
         c=0;
         flag_4=0;
         RIGHT=1;
         lock4=0;
         LEFT=0;
         delay_ms(1250);
         RIGHT=0;
        }

        /*if(((battery_1)+100) > (battery_2))
        {
         command(0xc0);
         data("battery_1 Mode");
         relay1=1;relay2=0;
         delay_ms(200);
        }

        if(((battery_2)+100) > (battery_1))
        {
         command(0xc0);
         data("battery_2 Mode");
         relay1=0;relay2=1;
         delay_ms(200);
        }*/


   }

}


void display1(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      n=n/10;
   }
   command(0x80);
   data("L1:");
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
   delay_ms(200);
}

void display2(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      n=n/10;
   }
   command(0xc0);
   data("2:");
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
   delay_ms(200);
}

void display3(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      n=n/10;
   }
   command(0x86);
   data(" 3:");
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
   delay_ms(200);
}

void display4(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      n=n/10;
   }
   command(0xc5);
   data(" 4:");
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
   delay_ms(200);
}


/*void display5(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      n=n/10;
   }
   command(0x8d);
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
   delay_ms(200);
}


void display6(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      n=n/10;
   }
   command(0xcd);
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
   delay_ms(200);
}*/

