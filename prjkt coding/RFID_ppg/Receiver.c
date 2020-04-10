#include<16f877a.h>
#use delay(clock=11059200)
#fuses hs,nowdt

#byte portc=0x07
#byte trisc=0x87

#byte portd=0x08
#byte trisd=0x88

#byte porte=0x09
#byte trise=0x89

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

#byte intcon=0x0b
#byte pir1=0x0c
#byte pie1=0x8c
#byte rcsta=0x18
#byte rcreg=0x1a
#byte txreg=0x19
#byte txsta=0x98
#byte spbrg=0x99
#bit rcif=pir1.5

unsigned long int x[12], i=0;

void command(unsigned char com)
{
portd=com;
reg=0;
rw=0;
en=1;
delay_ms(10);
en=0;
}
void data(unsigned char da)
{
portd=da;
reg=1;
rw=0;
en=1;
delay_ms(10);
en=0;
}
/*void display(int16 n)
{
int i,x[12];
for(i=0;i<=11;i++)
{
x[i]=n%10;
n=n/10;
}

}*/

void main()
{
portd=0x00;porte=0x00;portc=0x00;
trisd=0x00;trise=0x00;trisc=0x80;

intcon=0xc0;

pir1=0x00;
pie1=0x20;

rcsta=0x90;
rcreg=0x00;
txsta=0x20;
spbrg=0x11;

command(0x38);
command(0x06);
command(0x0c);
command(0x01);
delay_ms(30);

command(0x80);
data("Hi RFID");

while(1)
{
//display(a);
command(0x01);
command(0xc0);
data(x[11]|0x30);
data(x[10]|0x30);
data(x[9]|0x30);
data(x[8]|0x30);
data(x[7]|0x30);
data(x[6]|0x30);
data(x[5]|0x30);
data(x[4]|0x30);
data(x[3]|0x30);
data(x[2]|0x30);
data(x[1]|0x30);
data(x[0]|0x30);

if(rcif==1)
{
portc=0x01;
rcif=0;
command(0x80);
data("Hello");
x[i]=rcreg;
i++;

}
}
}
