#INCLUDE<16F877A.H>
#USE DELAY(CLOCK=11059200)

#BYTE PORTA=0X05
#BYTE TRISA=0X85

#BYTE PORTC=0X07
#BYTE TRISC=0X87

#DEFINE LDR 400

UNSIGNED INT16 VALUE=0;

void main()
{

   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_ccp1(CCP_PWM);
   setup_timer1();
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

WHILE(1)
{
   delay_ms(100);
   set_adc_channel(0);
   delay_us(100);         //wait for the acquisition time
   VALUE=read_adc();
   delay_us(4);

   if(value>LDR)
   {
    set_pwm1_duty(20);
   }
   ELSE
   {
   set_pwm1_duty(100);
   }
}
}
