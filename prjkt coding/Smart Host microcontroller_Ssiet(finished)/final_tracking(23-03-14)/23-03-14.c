#include <16F877A.h>
#fuses NOWDT,HS,PUT, NOPROTECT,BROWNOUT, NOLVP, NOCPD, NOWRT
#device adc=10
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_c6,rcv=PIN_c7, bits=8, errors)

#byte portb=0x06
#byte portc=0x07
#byte portd=0x08
#byte porte=0x09

#byte trisb=0x86
#byte trisc=0x87
#byte trisd=0x88
#byte trise=0x89

#byte intcon=0x0b
#byte rcreg=0x1a

#bit reg=portb.7
#bit rw=porte.1
#bit en=porte.2

#bit FORWARD=portb.0
#bit REVERSE=portb.1

#bit relay1=portb.4
#bit relay2=portb.5

#bit relay3=portc.0
#bit relay4=portc.1

unsigned int16 value1=0, value2=0, value3=0, value4=0, value5=0, value6=0;
unsigned char sec = 0, time = 0 , A=0 , GLAG = 0 , send = 0;
int1 flag=0,LDR1_FLAG=0,LDR2_FLAG=0,LDR3_FLAG=0,LDR4_FLAG=0;
int z=0 , B_1[4]={0} , B_2[4]={0} ,L_1[4]={0}, L_2[4]={0}, L_3[4]={0}, L_4[4]={0};
unsigned char MYARRAY[6]={0};
void display(unsigned int16);
void display1(unsigned int16);
void display2(unsigned int16);
void display3(unsigned int16);
void display4(unsigned int16);
void display5(unsigned int16);
void command(unsigned char com);
void data(unsigned char da);

#INT_RDA
RDA_ISR()
{
A=FGETC();
GLAG=1;
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

void main()
{
   portd=0x00;
   porte=0x00;

   trisd=0x00;
   trise=0x01;

   portb=0x00;
   trisb=0x00;

   portc=0x00;
   trisc=0x00;

   //option_reg=0x00;
	intcon=0xc0;

   enable_interrupts(global);
   enable_interrupts(int_rda);

   command(0x38); delay_ms(5);
   command(0x06); delay_ms(5);
   command(0x0c); delay_ms(5);
   command(0x01); delay_ms(5);

   command(0x80);
   data("SOLAR TRACKING");

   set_timer0(0x00); //set TMR0 initial value to zero
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); //set timer0 mode

   enable_interrupts(INT_TIMER0); //enable timer overflow interrupt

   enable_interrupts(GLOBAL); //enable global interrupt

   setup_adc( ADC_CLOCK_INTERNAL );
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4_AN5);

   delay_ms(2000);
   command(0x01);
   delay_ms(2);


   while(1)
   {
      if(GLAG==1)
      {
         if(A=='F')
         {
         relay3=1;
         relay4=0;
         GLAG=0;
      }
         else if(A=='R')
         {
         relay3=0;
         relay4=1;
         GLAG=0;
         }
         else if(A=='S')
         {
         relay3=0;
         relay4=0;
         GLAG=0;
         }
      }
      delay_ms(150);
      set_adc_channel(0);
      delay_us(100);         //wait for the acquisition time
      value1=read_adc();
      delay_us(4);

      delay_ms(150);
      set_adc_channel(1);
      delay_us(100);         //wait for the acquisition time
      value2=read_adc();
      delay_us(4);

      delay_ms(150);
      set_adc_channel(2);
      delay_us(100);         //wait for the acquisition time
      value3=read_adc();
      delay_us(4);

      delay_ms(150);
      set_adc_channel(3);
      delay_us(100);         //wait for the acquisition time
      value4=read_adc();
      delay_us(40);

      delay_ms(150);
      set_adc_channel(4);
      delay_us(100);         //wait for the acquisition time
      value5=read_adc();
      value5=value5*2;
      delay_us(40);

      delay_ms(150);
      set_adc_channel(5);
      delay_us(100);         //wait for the acquisition time
      value6=read_adc();
      value6=value6*2.5;
      delay_us(40);

      sprintf(myarray, "*B1%ld", value5);

      fputs(myarray);

      sprintf(myarray, "B2%ld", value6);

      fputs(myarray);

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
         send++;
         if(sec >= 12)
            sec = 0;
      }
      if(sec < 6)
      {
         z=0;
         command(0x80);
         data("L1:");
         display(value1);
         delay_ms(50);

         command(0x88);
         data("L2:");
         display1(value2);
         delay_ms(50);

         command(0xC0);
         data("L3:");
         display2(value3);
         delay_ms(50);

         command(0xC8);
         data("L4:");
         display3(value4);
         delay_ms(50);
         delay_ms(100);

      }

      else
      {
         z=1;
         command(0x80);
         data("BAT_1:");
         display4(value5);
         delay_ms(50);

         command(0xC0);
         data("BAT_2:");
         display5(value6);
         delay_ms(100);

      if((value5) > (value6))
      {
         command(0x8d);
         data("DIS");
      }
      if((value5) < (value6))
      {
         command(0x8d);
         data("CHA");

      }
      if((value6) > (value5))
      {
         command(0xcd);
         data("DIS");
      }
      if((value6) < (value5))
      {
         command(0xcd);
         data("CHA");
      }
    }
    if((value1>value2) && (value1>value3) && (value1>value4) && (LDR1_FLAG==0))
     {
         IF(LDR2_FLAG==1)
         {
         REVERSE=1;
         FORWARD=0;

         DELAY_MS(500);
         REVERSE=0;
         }
         ELSE IF(LDR3_FLAG==1)
         {
         FORWARD=1;
         REVERSE=0;
         DELAY_MS(1000);
          FORWARD=0;
         }
         ELSE IF(LDR4_FLAG==1)
         {
         FORWARD=1;
         REVERSE=0;
         DELAY_MS(500);
         FORWARD=0;
         }
         LDR1_FLAG=1;
         LDR2_FLAG=0;
         LDR3_FLAG=0;
         LDR4_FLAG=0;
    }


    if((value2>value1) && (value2>value3) && (value2>value4) && (LDR2_FLAG==0))
     {
         IF(LDR3_FLAG==1)
         {
         REVERSE=1;
         FORWARD=0;
         DELAY_MS(500);
         REVERSE=0;
         }
         ELSE IF(LDR4_FLAG==1)
         {
         FORWARD=1;
         REVERSE=0;
         DELAY_MS(1000);
         FORWARD=0;
         }
         ELSE IF(LDR1_FLAG==1)
         {
         FORWARD=1;
         REVERSE=0;
         DELAY_MS(500);
         FORWARD=0;
         }
         LDR1_FLAG=0;
         LDR2_FLAG=1;
         LDR3_FLAG=0;
         LDR4_FLAG=0;
     }



    if((value3>value1) && (value3>value2) && (value3>value4) && (LDR3_FLAG==0))
     {
         IF(LDR4_FLAG==1)
         {
         REVERSE=1;
         FORWARD=0;
         DELAY_MS(500);
         REVERSE=0;
         }
         ELSE IF(LDR1_FLAG==1)
         {
         FORWARD=1;
         REVERSE=0;
         DELAY_MS(1000);
         FORWARD=0;
         }
         ELSE IF(LDR2_FLAG==1)
         {
         FORWARD=1;
         REVERSE=0;
         DELAY_MS(500);
         FORWARD=0;
         }
         LDR1_FLAG=0;
         LDR2_FLAG=0;
         LDR3_FLAG=1;
         LDR4_FLAG=0;
    }


    if((value4>value1) && (value4>value2) && (value4>value3) && (LDR4_FLAG==0))
     {
         IF(LDR1_FLAG==1)
         {
         REVERSE=1;
         FORWARD=0;
         DELAY_MS(500);
         REVERSE=0;
         }
         ELSE IF(LDR2_FLAG==1)
         {
         FORWARD=1;
         REVERSE=0;
         DELAY_MS(1000);
         FORWARD=0;
         }
         ELSE IF(LDR3_FLAG==1)
         {
         FORWARD=1;
         REVERSE=0;
         DELAY_MS(500);
         FORWARD=0;
         }
         LDR1_FLAG=0;
         LDR2_FLAG=0;
         LDR3_FLAG=0;
         LDR4_FLAG=1;
     }

      if(((value5)+200) > (value6))
      {
         relay1=1;
         relay2=0;

      }
      if(((value6)+200) > (value5))
      {
         relay1=0;
         relay2=1;

      }

         /*sprintf (MYARRAY,"*B1%ldB2%ld", value5,value4); delay_ms(300);
         fputs("GRT EMB");
         fputs(MYARRAY);*/
        //sprintf(MYARRAY,"GRT EMB");
        /* delay_ms(100);
         PUTC('*');
         PUTC('B');
         PUTC('1');
         PUTC(B_2[3]|0x30);
         PUTC(B_2[2]|0x30);
         PUTC('.');
         PUTC(B_2[1]|0x30);
         PUTC(B_2[0]|0x30);

         PUTC('B');
         PUTC('2');
         PUTC(B_1[3]|0x30);
         PUTC(B_1[2]|0x30);
         PUTC('.');
         PUTC(B_1[1]|0x30);
         PUTC(B_1[0]|0x30);

         PUTC('L');
         delay_ms(300);
         PUTC('1');
         delay_ms(300);
         PUTC(L_1[3]|0x30);
         delay_ms(300);
         PUTC(L_1[2]|0x30);
         delay_ms(300);
         PUTC(L_1[1]|0x30);
         delay_ms(300);
         PUTC(L_1[0]|0x30);
         delay_ms(300);


        // PUTC('*');
         PUTC('L');
         delay_ms(300);
         PUTC('2');
         delay_ms(300);
         PUTC(L_2[3]|0x30);
         delay_ms(300);
         PUTC(L_2[2]|0x30);
         delay_ms(300);
         PUTC(L_2[1]|0x30);
         delay_ms(300);
         PUTC(L_2[0]|0x30);
         delay_ms(300);


        // PUTC('*');
         PUTC('L');
         delay_ms(300);
         PUTC('3');
         delay_ms(300);
         PUTC(L_3[3]|0x30);
         delay_ms(300);
         PUTC(L_3[2]|0x30);
         delay_ms(300);
         PUTC(L_3[1]|0x30);
         delay_ms(300);
         PUTC(L_3[0]|0x30);
         delay_ms(300);


         //PUTC('*');
         PUTC('L');
         delay_ms(300);
         PUTC('4');
         delay_ms(300);
         PUTC(L_4[3]|0x30);
         delay_ms(300);
         PUTC(L_4[2]|0x30);
         delay_ms(300);
         PUTC(L_4[1]|0x30);
         delay_ms(300);
         PUTC(L_4[0]|0x30);
         delay_ms(300);
*/

   }
}

void display4(unsigned int16 n)
{
   int i = 0;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      B_1[I] = n%10;
      n=n/10;
   }
   data(a[3]|0x30);
   data(a[2]|0x30);
   data(".");
   data(a[1]|0x30);
   data(a[0]|0x30);
}
void display5(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      B_2[I] = n%10;
      n=n/10;
   }

   data(a[3]|0x30);
   data(a[2]|0x30);
   data(".");
   data(a[1]|0x30);
   data(a[0]|0x30);
}
void display(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      L_1[I] = n%10;
      n=n/10;
   }

   data(a[3]|0x30);
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
}
void display1(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      L_2[I] = n%10;
      n=n/10;
   }

   data(a[3]|0x30);
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
}
void display2(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      L_3[I] = n%10;
      n=n/10;
   }

   data(a[3]|0x30);
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
}
void display3(unsigned int16 n)
{
   int i;
   int a[4];

   for(i=0;i<=3;i++)
   {
      a[i]=n%10;
      L_4[I] = n%10;
      n=n/10;
   }

   data(a[3]|0x30);
   data(a[2]|0x30);
   data(a[1]|0x30);
   data(a[0]|0x30);
}
