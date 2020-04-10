#include<16f877a.h>
#use delay(clock=11059200)
#use rs232(baud=9600,parity=N,xmit=pin_C6,rcv=pin_C7)

#byte portd=0x08
#byte trisd=0x88

#byte portb=0x06
#byte trisb=0x86

#byte pir1=0x0c
#byte pie1=0x8c
#byte rcsta=0x18
#byte rcreg=0x1a
#byte spbeg=0x99
#byte option_reg=0x81
#byte intcon=0x0b

int a[6]={0,0,0,0,0,0},i=0,longi=0,lat=0;
int1 flag=0;

#int_rda
rda_isr()
{
a[i]=fgetc();
i++;
if(i==5)
{
i=0;
flag=1;
}
}

void main()
{
portd=0x00;portb=0x00;
trisd=0x00;trisb=0x00;

pir1=0x00;
pie1=0x20;

rcsta=0x90;
rcreg=0x00;

intcon=0xe0;
option_reg=0x00;

while(1)
{
if(flag==1)
{
flag=0;
portd=0xff;
/*longi=10;
lat=15;
if(longi==10 && lat==15)
{
portd=0xff;
}*/
}
}
}



