#include<16f877a.h>
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_c6,rcv=PIN_c7)

#byte trisc=0x87
#byte portc=0x07

#byte portd=0x08
#byte trisd=0x88

#byte porte=0x09
#byte trise=0x89

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

#byte intcon=0x0b
#byte option_reg=0x81
#byte rcreg=0x1a

char a[20];
int i=0;
int1 flag=0,glag=0;

#int_rda
rda_isr()
{
a[i]=fgetC();
i++;
if(i==6)
{
i=0;
flag=1;
}
}
void command(unsigned int com)
{
portd=com;
reg=0;
rw=0;
en=1;
delay_ms(10);
en=0;
}

void data(unsigned int da)
{
portd=da;
reg=1;
rw=0;
en=1;
delay_ms(10);
en=0;
}
void main()
{
 portd=0x00;porte=0x00;portc=0x00;
 trisd=0x00;trise=0x00;trisc=0x80;

 command(0x38);
 command(0x06);
 command(0x0c);
 command(0x01);

 enable_interrupts(global);
 enable_interrupts(int_rda);

 delay_ms(300);
 command(0x80);
 data("GRT EMBEDDED");
 command(0xc0);
 data("SOLUTIONS");
 delay_ms(1500);
 command(0x01);

 while(1)
 {
 if(flag==1)
 {
 if(a[0]=='A' && a[1]=='B' && a[2]=='C' && a[3]=='D' && a[4]=='E' && a[5]=='F')
 {
 command(0x80);
 data("LED ARRAY");
 }flag=0;
 }
 }
}
