#include <16f877a.h>
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_c6,rcv=PIN_c7)
#fuses NOWDT,HS,PUT, NOPROTECT,BROWNOUT, NOLVP, NOCPD, NOWRT

#byte porta=0x05
#byte trisa=0x85

#byte portb=0x06
#byte trisb=0x86

#bit key=portb.0
#bit buzzer=0x06.1
#bit relay=0x06.2
#bit flow_meter=0x06.7

#byte portc=0x07
#byte trisc=0x87

#byte portd=0x08
#byte trisd=0x88

#byte porte=0x09
#byte trise=0x89

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

#byte tmr1h=0x0f
#byte tmr1l=0x0e
#byte t1con=0x10
#byte pir1=0x0c
#byte pie1=0x8c
#byte tmr0=0x01

#byte tmr2=0x11
#byte t2con=0x12
#byte pr2=0x92
#byte pir1=0x0c
#byte pie1=0x8c

#bit tmr1on=t1con.0

#byte option_reg=0x81
#byte intcon=0x0b

unsigned char value=0 ;
unsigned int16 count=0 , value_1=0 , count_1;
void gsm(unsigned char no);
void gsm1(unsigned char no);
void gsm2(unsigned char no);
void gsm3(unsigned char no);
void send(unsigned int16 o);
void send1(unsigned int16 y);
void DISPLAY_SEC(int m);
void DISPLAY_MINT(int n);
void DISPLAY_HOURS(int p);
unsigned char b=0,sec=0,mint=0,hours=0;
void display(unsigned int16 p);
void display1(unsigned int16 t);
INT D[5]={0},v[5]={0} , c[4]={0} , delay_count=0 ,k[4]={0} ;
int1 glag=0,flag=0,flag_1=0 , key_flag = 0 , paid = 0;

#INT_TIMER2
TIMER2_ISR()
{
   b++;
   if(b>=43)
   {
      b=0;
      flag=1;
      sec++;
      if(sec>=60)
      {
         sec=0;
         flag_1=1;
         mint++;
         if(mint>=60)
         {
            mint=0;
            hours++;
            if(hours==13)
            {
               hours=1;
            }
         }
      }
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
   trisd=0x00;
   trise=0x00;
   trisc=0x01;
   trisb=0x01;
   trisa=0x10;

   portd=0x00;
   portc=0x00;
   porte=0x00;
   portb=0x00;
   porta=0x00;

   tmr0=0x00;

   t1con=0x03;
   tmr1l=0x00;
   tmr1h=0x00;
   option_reg=0x20;

   intcon=0xc0;
   t2con=0x7e;
   tmr1on=1;
   tmr2=0x00;
   pie1=0x02;
   pir1=0x00;
   pr2=0xff;

   fputs("AT+CMGF=1");
   delay_ms(1000);

   fputs("AT+CNMI=1,2,0,0,0");
   delay_ms(1000);

   //fputs("AT+CMGR=1");
   //delay_ms(1000);

   command(0x38);
   command(0x06);
   command(0x0c);
   command(0x01);
   delay_ms(250);
   command(0x80);
   data("AUTOMATIC ENERGY");
   command(0xc0);
   data("METER USING GSM");
   delay_ms(2000);
   command(0x01);
   delay_ms(2);

   while(1)
   {
      if(key==0)
         key_flag=1;

      if((key==1) && (key_flag==1))
      {
         key_flag=0;
         paid=1;
      }
      delay_ms(100);
      command(0x80);
      data("H:MI:SE:");
      DISPLAY_SEC(sec);
      DISPLAY_MINT(mint);
      DISPLAY_HOURS(hours);

      delay_ms(100);
      command(0xc0);
      data("WATR:");
      count=make16(tmr1h,tmr1l);
      display1(count);

      if(count>=3000)
      {
         count=0;tmr1on = 0;
         flow_meter = 1 ;
         tmr1l=0;
         tmr1h=0;
      }
      delay_ms(10);
      command(0xc9);
      data("EB:");
      value=tmr0;
      display(value);

      if(flag_1==1)
      {
         flag_1=0;
         if((value>1) || (count>1))
         {
            value_1=(int16)value*5;
            send(value_1);
            count_1=(int16)count*1;
            send1(count_1);
            GSM(0);
            DELAY_MS(500);
            GSM(1);
            delay_ms(500);
            GSM1(0);
            DELAY_MS(500);
            GSM1(1);
            delay_ms(500);
            GSM2(0);
            delay_ms(500);
            GSM3(0);
         }
      }

      if(value>10)
      {
         if((delay_count==0) && (relay==1))
            buzzer=1;

         if(delay_count>=1)
            buzzer=0;

         if(flag==1)
         {
            flag=0;
            delay_count++;
         }
         if((paid==1) && (delay_count<10))
         {
            paid=0;
            relay=0;
            value=0;
            tmr0=0;
            delay_count=0;
         }
         else if((delay_count>=10) && (paid==0))
         {
            value=0;
            relay=1;
            tmr0=0;
            delay_count=0;
         }
      }
   }
}

void display1(unsigned int16 t)
{
   int m=0,q[4];
   for(m=0;m<=3;m++)
   {
      q[m]=t%10;
      v[m]=t%10;
      t=t/10;
   }
   command(0xc5);
   data(q[3]|0x30);
   data(q[2]|0x30);
   data(q[1]|0x30);
   data(q[0]|0x30);
}
void display(unsigned int16 p)
{
   int L=0,W[4];
   for(L=0;L<=3;L++)
   {
      W[L]=p%10;
      D[L]=p%10;
      p=p/10;
   }
   command(0xcc);
   data(W[3]|0x30);
   data(W[2]|0x30);
   data(W[1]|0x30);
   data(W[0]|0x30);
}

void DISPLAY_SEC(int m)
{
   INT X[2],I=0;
   FOR(I=0;I<2;I++)
   {
      X[I]=m%10;
      m=m/10;
   }
   COMMAND(0X8E);
   DATA(X[1]|0X30);
   DATA(X[0]|0X30);
}
void DISPLAY_MINT(int n)
{
   INT Y[2],J=0;
   FOR(J=0;J<2;J++)
   {
      Y[J]=n%10;
      n=n/10;
   }
   COMMAND(0X8B);
   DATA(Y[1]|0X30);
   DATA(Y[0]|0X30);
   command(0x8D);
   DATA(":");
}
void DISPLAY_HOURS(int p)
{
   INT Z[2],K=0;
   FOR(K=0;K<2;K++)
   {
      Z[K]=p%10;
      p=p/10;
   }
   COMMAND(0X88);
   DATA(Z[1]|0X30);
   DATA(Z[0]|0X30);
   command(0x8A);
   DATA(":");
}
void send(unsigned int16 o)
{
   int g=0;
   for(g=0;g<=3;g++)
   {
      c[g]=o%10;
      o=o/10;
   }
}

void send1(unsigned int16 y)
{
   int g=0;
   for(g=0;g<=3;g++)
   {
      k[g]=y%10;
      y=y/10;
   }
}
void gsm(unsigned char no)
{
   if(no==0)
      puts("AT+CMGS=\"+919944296357\"");  //+919597826505
   else
      puts("AT+CMGS=\"+919944439363\"");  //918807155896

   putc(D[3]|0X30);
   putc(D[2]|0X30);
   putc(D[1]|0X30);
   putc(D[0]|0X30);
   PUTS("UNITS");
   putc(0x1A);
}
void gsm1(unsigned char no)
{
   if(no==0)
      puts("AT+CMGS=\"+919944296357\"");  //+919597826505
   else
      puts("AT+CMGS=\"+919944439363\"");  //918807155896

   putc(v[3]|0X30);
   putc(v[2]|0X30);
   putc(v[1]|0X30);
   putc(v[0]|0X30);
   PUTS("LPM");
   putc(0x1A);
}
void gsm2(unsigned char no)
{
   if(no==0)
      puts("AT+CMGS=\"+919944296357\"");  //+919597826505
   else
   puts("AT+CMGS=\"+919944439363\"");  //918807155896
   putc(c[3]|0x30);
   putc(c[2]|0x30);
   putc(c[1]|0x30);
   putc(c[0]|0x30);
   puts(" RUPEES FOR EB");
   putc(0x1A);
}
void gsm3(unsigned char no)
{
   if(no==0)
      puts("AT+CMGS=\"+919944296357\"");  //+919597826505
   else
   puts("AT+CMGS=\"+919944439363\"");  //918807155896
   putc(k[3]|0x30);
   putc(k[2]|0x30);
   putc(k[1]|0x30);
   putc(k[0]|0x30);
   puts(" RUPEES FOR WATER");
   putc(0x1A);
}
