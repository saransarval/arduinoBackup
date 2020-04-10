#include "tx_header.h"

unsigned int A[4] = {0}, dummy = 0;
unsigned char ldr_dummy[2] = {0};
unsigned int16 adc_value = 0;
int32 total_distance1=0,time1=0;
INT I=0,b=0,c=0,t=0, receive = 0;
INT1 FLAG=0, flag1 = 0;
void display(int16 value);
//void function1(int16 an_value);
int1 tx_rtr=0;
int1 tx_ext=1;
int tx_pri=1;
int out_data[2];
void command(unsigned char com);
void data(unsigned char da);

#ZERO_RAM

/*#int_CANRX0
CANRX0_isr()
{
	CAN_INT_RXB0IF=0;

	can_getd(rx_id,&in_data[0],rx_len,rxstat);
	can_int_enable=1;
}

#int_RDA

RDA_isr()
{
   A[3] = A[2];
   A[2] = A[1];
   A[1] = A[0];
   A[0] = getc();
   FLAG1 = 1;
}*/


#int_timer0
timer0_isr()
{
   c++;
   b++;
}


#int_ext
ext_isr()
 {
      disable_interrupts(int_timer0);
      //time1=(a*0.023+tmr0*92.60)-410;  //time1 in micro sec.....
      time1=(0.5*344)*(((int32)c*43)+((int32)tmr0l*0.36));
     //time1=((a*0.023)+tmr0*92.16)-410;
      flag=1;
      disable_interrupts(int_ext);
      c=0;

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
   /*setup_wdt(WDT_OFF);
   //setup_timer_0(RTCC_INTERNAL);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);
   setup_timer_1(T1_DISABLED);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_low_volt_detect(FALSE);
   setup_oscillator(False);
   setup_ccp1(CCP_PWM);
   setup_timer_2(t2_DIV_BY_16,124,1);*/
   setup_wdt(WDT_OFF);
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);
   setup_timer_1 ( T1_INTERNAL | T1_DIV_BY_4 );
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   setup_timer_2(T2_DISABLED,1,2);
   setup_comparator(NC_NC_NC_NC);
   setup_low_volt_detect(FALSE);
   setup_oscillator(False);
   
   porta = 0x00;
   trisa = 0x01;
   
   portb = 0x00;
   trisb = 0x00;
   
   portc = 0x00;
   trisc = 0x01;
   
   portd = 0x00;
   trisd = 0x00;
   
   porte = 0x00;
   trise = 0x00;
   
   intcon = 0xc0;
   t1con = 0x06;
   tmr1l = 0x00;
   tmr1h = 0x00;
   
   command(0x38);
   command(0x06);
   command(0x0c);
   command(0x01);
   delay_ms(100);

   //intcon2=0x00;
   /*fputs("AT+CMGF=1");
   delay_ms(1000);


   fputs("AT+CNMI=1,2,0,0,0");
   delay_ms(1000);*/
   
   command(0x80);
   data("CAN BASED MONIT");
   command(0xc0);
   data("FAULT DIAGONSTICS");
   delay_ms(2000);
   command(0x01);
   
   can_init();
   delay_ms(5000);
   
   TRIG=0;
   delay_us(10);
   TRIG=1;
   delay_us(10);
   TRIG=0;
   delay_us(10);
   enable_interrupts(int_timer0);
   //enable_interrupts(INT_CANRX0);
   enable_interrupts(INT_EXT);
   //enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   while(1)
   {
    
      delay_ms(10);
      set_adc_channel( 0 );
      adc_value = read_adc();
      display(adc_value);
   
    /*if(can_int_enable==1)
    {
      can_int_enable=0;

      ldr_dummy[0]=in_data[0];
      ldr_dummy[1]=in_data[1];
      ldr_value=ldr_dummy[1];
      ldr_value<<=8;
      ldr_value+ldr_dummy[0];
            if(ldr_value > LDR)
            {
               set_pwm1_duty (60);
            }
            else
            {
               //delay_ms(10);
               set_pwm1_duty (120);
            }
     }


      if(FLAG1==1)
      {
         FLAG1=0;
         if(A[2] == '@')
         {
            if(((A[1]=='6') && (A[0]=='0'))||
            ((A[1]=='5') && (A[0]=='0'))||
            ((A[1]=='4') && (A[0]=='0'))||
            ((A[1]=='3') && (A[0]=='0'))||
            ((A[1]=='2') && (A[0]=='0')))
            {
               out_data[0] = a[1];
               out_data[1] = a[0];
               can_putd(0x01,     out_data,   2,   tx_pri,      tx_ext,    tx_rtr);
               putc(a[1]);
               putc(a[0]);
               putc(' ');
               putc(' ');
            }
         }
      }*/

      if(b>=3)
      {
         b=0;
         time1=0;
         TRIG=0;
         delay_us(10);
         TRIG=1;
         delay_us(10);
         TRIG=0;
         delay_us(10);
      }

      if(flag==1)
      {
         disable_interrupts(int_ext);
         disable_interrupts(int_timer0);
         flag=0;
         total_distance1=(time1);      // velocity of sound 350 m/sec   =  0.35mm /usec)
         //total_distance1=(time1*3.5)/2;

         //function1(total_distance1);
         enable_interrupts(int_ext);
         enable_interrupts(int_timer0);

         if(total_distance1>=23000)
         {
         buzzer=0;
         //puts("AAA");
         }
         else
         {
         buzzer=1;
         }
        }
      }
   }
   
void display(unsigned int16 value)
{
   int z[4],j=0;
   for(j=0;j<=3;j++)
   {
      z[j]=value%10;
      value=value/10;
   }
   command(0xc0);
   data(z[3]|0x30);
   data(z[2]|0x30);
   data(z[1]|0x30);
   data(z[0]|0x30);

}   

/*void function1(int16 an_value)
   {
      int8 a1[7]={0},i4=0;

      for(i4=0;i4<6;i4++)
         {
            a1[i4]=an_value%10;
            an_value=an_value/10;
         }
      fputc(a1[5]|0x30);
      fputc(a1[4]|0x30);
      fputc(a1[3]|0x30);
      putc('.');
      fputc(a1[2]|0x30);
      fputc(a1[1]|0x30);
      fputc(a1[0]|0x30);
      fputs("CM");
      putc(' ');
      putc(' ');
  }*/
