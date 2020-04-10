#include<16f877a.h>
#device adc=10
#use delay(clock=11059200)
#fuses NOWDT, HS, NOPUT, NOPROTECT, NOBROWNOUT, NOLVP, NOCPD, NOWRT

#byte porta=0x05
#byte portb=0x06
#byte portc=0x07
#byte portd=0x08
#byte porte=0x09

#byte trisa=0x85
#byte trisb=0x86
#byte trisc=0x87
#byte trisd=0x88
#byte trise=0x89

#byte option_reg=0x81
#byte intcon=0x0b

#bit reg=porte.0
#bit rw=porte.1
#bit en=porte.2

#bit RF_1=portb.4
#bit RF_2=portb.5
#bit RF_3=portb.6
#bit RF_4=portb.7

#bit FORWARD=portb.0
#bit REVERSE=portb.1

#bit BATTERY_1=portb.2
#bit BATTERY_2=portb.3

#bit MOTOR1_P = portc.0
#bit MOTOR1_N = portc.1

#bit MOTOR2_P = portc.6
#bit MOTOR2_N = portc.7

#bit MOTOR3_P = portc.2
#bit MOTOR3_N = portc.3

#bit MOTOR4_P = portc.5
#bit MOTOR4_N = portc.4

unsigned int16 value1=0, value2=0, value3=0, value4=0;
unsigned char sec = 0, time = 0 , A=0 , GLAG = 0;
int1 flag=0, LDR1_FLAG=0, LDR2_FLAG=0;
int z=0 , b[4]={0};
void display(unsigned int16 n);
void command(unsigned char com);
void data(unsigned char da);

#INT_RB
RB_ISR()
{
      while(RF_1==1)
      {
        MOTOR1_P=1; MOTOR2_P=1; MOTOR3_P=1; MOTOR4_P=1; 
      }
        RF_1=0;
      while(RF_2==1)
      {
        MOTOR1_N=1; MOTOR2_N=1; MOTOR3_N=1; MOTOR4_N=1; 
      }
        RF_2=0;
      while(RF_3==1)
      {
        MOTOR1_P=1; MOTOR4_P=1;  
      }
        RF_3=0;
      while(RF_4==1)
      {
        MOTOR3_P=1; MOTOR2_P=1; 
      }
        RF_4=0; MOTOR3_P=0; MOTOR2_P=0; MOTOR1_P=0; MOTOR4_P=0; MOTOR1_N=0; MOTOR2_N=0; MOTOR3_N=0; MOTOR4_N=0;
}

#int_TIMER0
TIMER0_isr()
{
   time++;
   if(time>=43)
   {
      time=0;
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

   portd=0x00;
   trisd=0x00;

   porte=0x00;
   trise=0x00;

   portb=0x00;
   trisb=0xf0;

   portc=0x00;
   trisc=0x00;

   option_reg=0x00;
	intcon=0xc8;

   command(0x38);
   command(0x06);
   command(0x0c);

   delay_ms(100);
   command(0x80);
   data("SOLAR TRACKING");

   set_timer0(0x00); //set TMR0 initial value to zero
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); //set timer0 mode

   enable_interrupts(INT_TIMER0); //enable timer overflow interrupt

   enable_interrupts(GLOBAL); //enable global interrupt

   setup_adc( ADC_CLOCK_INTERNAL );
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);

   delay_ms(2000);
   command(0x01);
   delay_ms(2);

   while(1)
   {

         delay_ms(100);
         set_adc_channel(0);
         delay_us(100);         //wait for the acquisition time
         value1=read_adc();
         delay_us(4);

         delay_ms(10);
         set_adc_channel(1);
         delay_us(100);         //wait for the acquisition time
         value2=read_adc();
         delay_us(4);

         delay_ms(10);
         set_adc_channel(2);
         delay_us(100);         //wait for the acquisition time
         value3=read_adc();
         value3=(value3*1.8);
         delay_us(4);

         delay_ms(10);
         set_adc_channel(3);
         delay_us(100);         //wait for the acquisition time
         value4=read_adc();
         value4=(value4*2);
         delay_us(40);


         if((sec==0)|| (sec==06))
         {
            delay_ms(100);
            command(0x01);
            delay_ms(2);
         }

         if(flag==1)
         {
            flag=0;
            sec++;
              if(sec >= 12)
               sec = 0;
         }
             if(sec < 6)
              {
                  z=0;
                  command(0x80);
                  data("L1:");
                  display(value1);

                  command(0xc0);
                  data("L2:");
                  display(value2);

              }
             else if(sec>=6)
               {
                  z=1;
                  command(0x80);
                  data("BATTERY1:");
                  display(value3);

                  command(0xC0);
                  data("BATTERY2:");
                  display(value4);
                  
                  if((value3) > (value4))
                  {
                  command(0x8d);
                  data("DIS");
                  }
                  if((value3) < (value4))
                  {
                  command(0x8d);
                  data("CHA");
                  
                  }
                  if((value4) > (value3))
                  {
                  command(0xcd);
                  data("DIS");
                  }
                  if((value4) < (value3))
                  {
                  command(0xcd);
                  data("CHA");
                  }

               }

             if((value1>value2) && (LDR1_FLAG==0))
              {
                  IF(LDR2_FLAG==1)
                   {
                     REVERSE=1;
                     FORWARD=0;
                     DELAY_MS(500);
                     REVERSE=0;
                   }
                     LDR1_FLAG=1;
                     LDR2_FLAG=0;
              }


             if((value2>value1) && (LDR2_FLAG==0))
              {
                  IF(LDR1_FLAG==1)
                   {
                     FORWARD=1;
                     REVERSE=0;
                     DELAY_MS(500);
                     FORWARD=0;
                   }
                     LDR1_FLAG=0;
                     LDR2_FLAG=1;
              }

             if(((value3)+100) > (value4))
              {
                     BATTERY_1=1;
                     BATTERY_2=0;
              }

             if(((value4)+100) > (value3))
              {
                     BATTERY_1=0;
                     BATTERY_2=1;
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
      B[I] = n%10;
      n=n/10;
   }

   data(a[3]|0x30);
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);

   if(z==1)
   {
   command(0x8b);
   data('.');
   command(0xcb);
   data('.');
   }
   delay_ms(100);
}

