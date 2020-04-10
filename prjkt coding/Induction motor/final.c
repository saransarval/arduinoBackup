#INCLUDE<16F877A.H>
#USE DELAY(CLOCK=11059200)
#use rs232(baud=9600,parity=N,xmit=pin_C6,rcv=pin_C7)

#BYTE TRISA=0X85
#BYTE TRISB=0X86
#BYTE TRISC=0X87
#BYTE TRISD=0X88
#BYTE TRISE=0X89

#BYTE PORTA=0X05
#BYTE PORTB=0X06
#BYTE PORTC=0X07
#BYTE PORTD=0X08
#BYTE PORTE=0X09

///////////////////////
//////INTERRUPT/////////
///////////////////////
#BYTE INTCON=0X0B
#BYTE PIE1=0X8C
#BYTE PIR1=0X0C
#BYTE OPTION_REG=0X81
#BIT RCIF=PIR1.5
///////////////////////
//////LCD PINS/////////
///////////////////////

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

///////////////////////
//////adc PINS/////////
///////////////////////

#bit GO=0x1f.2

#byte adcon0=0x1f
#byte adcon1=0x9f
#byte adresh=0x1e
#byte adresl=0x9e

///////////////////////
//////PWM PINS/////////
///////////////////////
#byte tmr2=0x11
#byte pr2=0x92
#byte ccpr1h=0x16
#byte ccpr1l=0x15
#byte ccp1con=0x17
#byte t2con=0x12

#DEFINE PWM CCPR1L
#DEFINE ON 200
#DEFINE ON_1 100
#DEFINE OFF 0

///////////////////////
//////SPEED PINS/////////
///////////////////////
#byte tmr1h=0x0f
#byte tmr1l=0x0e
#byte t1con=0x10
#byte tmr0=0x01

#bit tmr0ie=intcon.5

#bit tmr1on=t1con.0
#bit tmr1ie=pie1.0
#bit KEY = PORTB.0

int i=0, tm=0 , b = 0 , A = 0 , TIME=0, SEC=0 ;
int16 count=0 , speed=0 , c=0, t=0 ,value=0, ADC=0, CURRENT=0, VOLTAGE=0;
unsigned char SPEED_RANGE[5] = {100 , 500 , 1000 , 1500 , 2000} , SPEED_LIMIT = 5; 
void display_num(unsigned int16 num);
void gsm(unsigned char no);
void rpm(unsigned int16 s);
int1 TERMINATE=0, CHECK=0, OOPS=0 , flag = 0;

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

#INT_TIMER0
timer0_isr()
{
   tm++;
   B++;
      if(tm>=43)
         {
            tm=0;
            flag=1;
         }
}

VOID MAIN()
{

   TRISA=0X03;
   TRISB=0X01;
   TRISC=0X01;
   TRISD=0X00;
   TRISE=0X00;
   
   PORTA=0X00;
   PORTB=0X00;
   PORTC=0X00;
   PORTD=0X00;
   PORTE=0X00;
   
   PR2=0XFF;
   CCP1CON=0X0F;
   T2CON=0X7D;
   CCPR1L=0X00;
   TMR2=0X00;
   
   //TMR0IE=1;
   TMR0=0;
   T1CON=0X07;
   TMR1H=0X00;
   TMR1L=0X00;
   
   INTCON=0XC8;                        
   PIE1=0X00;                          /////  ENABLE ADC INTERRUPT ///////////
   PIR1=0X00;                          /////  INTERRUPT FLAGS////////////////////////////////////////
   OPTION_REG=0X07;
   
   adresh=0x00;
   adresl=0x00;
   adcon1=0x82;
   
   COMMAND(0X38);
   COMMAND(0X06);
   COMMAND(0X0C);
   COMMAND(0X01);
   
   DELAY_MS(100);
   COMMAND(0X80);
   DATA("INDUCTION MOTOR");
   COMMAND(0XC0);
   DATA("FAULT DETECTION");
   DELAY_MS(2000);
   
   COMMAND(0X01);
   DELAY_MS(2);
   ENABLE_INTERRUPTS(GLOBAL);          /////  INBUILT FUCTION TO ENABLE THE TIMER0
   ENABLE_INTERRUPTS(INT_EXT);         /////  INBUILT FUNCTION TO ENABLE UART RECEPTION
   ENABLE_INTERRUPTS(INT_TIMER0);      /////  T0 ENABLE GIE,PEIE INTERRUPT, PORT CHANGE INTERRUPT////
   
   delay_ms(10);

WHILE(1)
{
   COMMAND(0X80);
   DATA("C:");
   COMMAND(0X87);
   DATA("A");
   CURRENT=MAKE16(adresh , adresl);
   DELAY_MS(10);
   CURRENT=CURRENT/2;
   DISPLAY_NUM(CURRENT);
   VOLTAGE=MAKE16(adresh , adresl);
   DELAY_MS(10);
   COMMAND(0X87);
   DATA("V:");
   DISPLAY_NUM(VOLTAGE);

IF(KEY==0)
{
   DELAY_MS(100);
   A++;  
}
IF(A==1)
{
   SPEED_LIMIT = 5;
   COMMAND(0XC0);
   DATA("MOTOR ON");
}
ELSE IF(A==2)
{
   SPEED_LIMIT = 3;
   DATA("MOTOR ON"); 
}
ELSE 
{
   SPEED_LIMIT = 0;
   DATA("MOTOR OFF");
}
IF(TERMINATE==0)
{
   if(flag==1)
   {  
      flag = 0;
      count=make16(tmr1h,tmr1l);
      speed = count * 3.14;
      rpm(speed);
      
      tmr1on=0;
      tmr1h=0x00;
      tmr1l=0x00;
      tmr1on=1;
      tmr0=0x00;
   }
}
IF(CURRENT>450)
{
   IF(b>=3)
   {
      b=0;
      TERMINATE=1;
   }
}

IF(TERMINATE==1)
{
   PWM=OFF;
   COMMAND(0X80);
   DATA("OVER LOADING    ");
   COMMAND(0XC0);
   DATA("PLZ CHECK LOAD  ");
}
}
}

void display_num(unsigned int16 num)
{
   int a[5],i;
   
   for(i=0;i<4;i++)
   {
   a[i]=num%10;
   num=num/10;
   }
   data(a[3]|0X30);
   data(a[2]|0X30);
   data(a[1]|0X30);
   data(a[0]|0X30);
   delay_ms(100);
}

void rpm(unsigned int16 s)
{
   int j, z[4]={0};
   for(j=0;j<=3;j++)
   {
   z[j] = s%10;
   s = s/10;
   }
   command(0xc8);
   data(z[3]|0x30);
   data(z[2]|0x30);
   data(z[1]|0x30);
   data(z[0]|0x30);
   delay_ms(100);
}

