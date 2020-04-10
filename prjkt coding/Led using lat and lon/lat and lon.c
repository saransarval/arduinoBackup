#include<16f877a.h>
#use delay(clock=110592000

#byte portd=0x08
#byte trisd=0x88

#byte portb=0x06
#byte trisb=0x86

#byte tmr0=0x01
#byte option_reg=0x81
#byte intcon=0x0b

int lat=0,lon=0,a=0;

#int_timer0
timer0_isr()
{
a++;
if(a<=43)
{
a=0;
lat++;
lon++;
}
}
void main()
{
portd=0x00;
trisd=0x00;
intcon=0xe0;
tmr0=0x00;
option_reg=0x07;

while(1)
{
if(lat==10 && lon==10)
{
delay_ms(250);
portd=0x01;
}
}
}
