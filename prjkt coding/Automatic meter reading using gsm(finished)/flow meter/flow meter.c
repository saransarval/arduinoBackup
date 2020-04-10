#include<16f877a.h>
#device adc=10
#use delay(clock=11059200)

#byte portc=0x07
#byte trisc=0x87

#byte portd=0x08
#byte trisd=0x88

#byte porte=0x09
#byte trise=0x89

#byte option_reg=0x81
#byte intcon=0x0b

#byte tmr1h=0x0f
#byte tmr1l=0x0e
#byte t1con=0x10

#byte tmr0=0x01
#byte pir1=0x0c
#byte pie1=0x8c

#bit tmr0ie=intcon.5

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

int b=0,sec=0,mint=0;
unsigned int16 count=0;
int1 flag=0;
void display(unsigned int16 n);
void display_sec(int n);
void display_mint(int q);

#int_timer0
timer0_isr()
{
b++;
if(b==43)
{
b=0;
sec++;
}
if(sec>=60)
{
sec=0;
mint++;flag=1;
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

void data(unsigned int da)
{
portd=da;
reg=1;rw=0;
en=1;
delay_ms(1);
en=0;
}

void main()
{
portc=0x00;portd=0x00;porte=0x00;
trisc=0x01;trisd=0x00;trise=0x00;

t1con=0x07;
tmr1l=0x00;
tmr1h=0x00;

option_reg=0x07;
intcon=0xc0;
tmr0=0x00;
tmr0ie=0;
delay_ms(2);

command(0x38);
command(0x06);
command(0x0c);
command(0x01);

delay_ms(250);

command(0x80);
data("FLOW METER");

delay_ms(1000);
command(0x01);

while(1)
{
delay_ms(100);
command(0xc0);
data("MINT_SEC:");
display_sec(sec);
delay_ms(300);
display_mint(mint);
command(0x80);
data("FLOW MTR:");
delay_ms(100);
display(count);
count=make16(tmr1h,tmr1l);
if(count>=1)
{
tmr0ie=1;
}
if(mint>=1)
{
mint=0;
count=0;
tmr0ie=0;
tmr1l=0x00;
tmr1h=0x00;
}
}
}

void display_mint(int q)
{
int v[2],s=0;
for(s=0;s<=1;s++)
{
v[s]=q%10;
q=q/10;
}
command(0xc9);
data(v[1]|0x30);
data(v[0]|0x30);
data(":");
}
void display_sec(int n)
{
int x[2],i=0;
for(i=0;i<=1;i++)
{
x[i]=n%10;
n=n/10;
}
command(0xcc);
data(x[1]|0x30);
data(x[0]|0x30);
}

void display(unsigned int16 n)
{
int c[4],k=0;
for(k=0;k<=3;k++)
{
c[k]=n%10;
n=n/10;
}
command(0x89);
data(c[3]|0x30);
data(c[2]|0x30);
data(c[1]|0x30);
data(c[0]|0x30);
delay_ms(250);
}
