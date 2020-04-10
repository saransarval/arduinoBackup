#include "rx_header.h"

unsigned char temp[4] ={0} , speed_turbine[4] ={0} , oil_level[4] = {0} , vibration[4] = {0};
int1 key1_flag = 0, tmr0_flag = 0 , lock_1 = 1 , lock_2 = 1 , lock_3 = 1 , lock_4 = 1;
int16 adc_value = 0;
void command(unsigned char com);
void data(unsigned char da);
void display(unsigned int16 value);
void display_speed(int16 value);
void gsm(unsigned char no);
void gsm1(unsigned char no);
void gsm2(unsigned char no);
void gsm3(unsigned char no);

int1 tx_rtr=0;
int1 tx_ext=1;
int tx_pri=1;
//int in_data[4];

#ZERO_RAM

#int_CANRX0
CANRX0_isr()
{
	CAN_INT_RXB0IF=0;

	can_getd(rx_id,&in_data[0],rx_len,rxstat);
	can_int_enable=1;
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
//   CONFIG1H = 0x0;
         unsigned int16 cal_var=0;
         setup_psp(PSP_DISABLED);
         setup_spi(FALSE);
         setup_wdt(WDT_OFF);
         setup_comparator(NC_NC_NC_NC);
         setup_vref(FALSE);

         setup_low_volt_detect(FALSE);
         setup_oscillator(False);
         delay_ms(10);

         trisd = 0x00;
         trise = 0x00;
         trisc = 0x80;
         trisb = 0x17;
         portd = 0x00;
         porte = 0x00;
         portc = 0x00;
         portb = 0x00;
         porta = 0x00;
         trisa = 0x00;

         intcon2=0x00;

         command(0x38);
         command(0x06);
         command(0x0c);
         command(0x01);
         delay_ms(2);

         fputs("AT+CMGF=1");
         delay_ms(1000);

         fputs("AT+CNMI=1,2,0,0,0");
         delay_ms(1000);

         command(0x80);
         data("CAN BASED MONI");
         command(0xc0);
         data("FAULT DIAGNOSTICS");
         delay_ms(2000);
         command(0x01);
         delay_ms(2);

         can_init();
         delay_ms(10);
         command(0x80);
         enable_interrupts(INT_CANRX0);
         enable_interrupts(GLOBAL);
while(1)
{
     if(can_int_enable==1)
        {
         can_int_enable = 0;
         if(rx_id==0x01)
         {
         temp[0]=in_data[0];
         temp[1]=in_data[1];
         temp[2]=in_data[2];
         temp[3]=in_data[3];
         command(0xc0);
         data("T:");
         data(temp[3]|0x30);
         data(temp[2]|0x30);
         data(temp[1]|0x30);
         data(temp[0]|0x30);
         cal_var = (temp[3]*1000)+(temp[2]*100)+(temp[1]*10)+temp[0];
         if((cal_var>=0050) && (lock_1==1))
         {

         gsm1(0);
         lock_1=0;
         }
         //lock_1=1;
        }

        else if(rx_id==0x02)
        {
        vibration[0]=in_data[0];
        vibration[1]=in_data[1];
        vibration[2]=in_data[2];
        vibration[3]=in_data[3];
        command(0xc8);
        data("V:");
        data(vibration[3]|0x30);
        data(vibration[2]|0x30);
        data(vibration[1]|0x30);
        data(vibration[0]|0x30);
        cal_var = (vibration[3]*1000)+(vibration[2]*100)+(vibration[1]*10)+vibration[0];
         if((cal_var>=0500) && (lock_2==1))
         {

         gsm3(0);
         lock_2=0;
         }
         //lock_2=1;
       }
        else if(rx_id==0x03)
        {
        speed_turbine[0]=in_data[0];
        speed_turbine[1]=in_data[1];
        speed_turbine[2]=in_data[2];
        speed_turbine[3]=in_data[3];
        command(0x80);
        data("S:");

        data(speed_turbine[3]|0x30);
        data(speed_turbine[2]|0x30);
        data(speed_turbine[1]|0x30);
        data(speed_turbine[0]|0x30);
         cal_var =(speed_turbine[3]*1000)+(speed_turbine[2]*100)+(speed_turbine[1]*10)+speed_turbine[0];
         if((cal_var<=00060) && (lock_4==1))
         {

         gsm(0);
         lock_4=0;
         }
         //lock_4=1;
        }

        else if(rx_id==0x04)
        {
        oil_level[0]=in_data[0];
        oil_level[1]=in_data[1];
        oil_level[2]=in_data[2];
        oil_level[3]=in_data[3];
        command(0x88);
        data("O:");
        data(oil_level[3]|0x30);
        data(oil_level[2]|0x30);
        data(oil_level[1]|0x30);
        data(oil_level[0]|0x30);
        cal_var = (oil_level[3]*1000)+(oil_level[2]*100)+(oil_level[1]*10)+oil_level[0];
         if((cal_var>=0050) && (lock_3==1))
         {

         gsm2(0);
         lock_3=0;
         }
         //lock_3=1;
        }
      }
      delay_ms(100);
      PUTC('$');
      PUTC(temp[0]|0X30);
      PUTC(temp[1]|0X30);
      PUTC(temp[2]|0X30);
      PUTC(temp[3]|0X30);

      PUTC(speed_turbine[0]|0X30);
      PUTC(speed_turbine[1]|0X30);
      PUTC(speed_turbine[2]|0X30);
      PUTC(speed_turbine[3]|0X30);

      PUTC(oil_level[0]|0X30);
      PUTC(oil_level[1]|0X30);
      PUTC(oil_level[2]|0X30);
      PUTC(oil_level[3]|0X30);

      PUTC(vibration[0]|0X30);
      PUTC(vibration[1]|0X30);
      PUTC(vibration[2]|0X30);
      PUTC(vibration[3]|0X30);
      PUTC('#');
      delay_ms(2000);
      PUTC(0X0d);

   }
}

void gsm(unsigned char no)
{
if(no==0)
puts("AT+CMGS=\"8056308831\"");
puts("SPEED");
putc(speed_turbine[3]|0x30);
putc(speed_turbine[2]|0x30);
putc(speed_turbine[1]|0x30);
putc(speed_turbine[0]|0x30);
putc(0x1A);
}
void gsm1(unsigned char no)
{
if(no==0)
puts("AT+CMGS=\"8056308831\"");
puts("TEMP");
putc(temp[3]|0x30);
putc(temp[2]|0x30);
putc(temp[1]|0x30);
putc(temp[0]|0x30);
putc(0x1A);
}
void gsm2(unsigned char no)
{
if(no==0)
puts("AT+CMGS=\"8056308831\"");
puts("OIL LEVEL");
putc(oil_level[3]|0x30);
putc(oil_level[2]|0x30);
putc(oil_level[1]|0x30);
putc(oil_level[0]|0x30);
putc(0x1A);
}
void gsm3(unsigned char no)
{
if(no==0)
puts("AT+CMGS=\"8056308831\"");
puts("VIBRATION");
putc(vibration[3]|0x30);
putc(vibration[2]|0x30);
putc(vibration[1]|0x30);
putc(vibration[0]|0x30);
putc(0x1A);
}
