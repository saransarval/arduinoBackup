#include<16f877a.h>
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_C6,rcv=PIN_C7)

#byte porta=0x06
#byte trisa=0x86

#byte portb=0x06
#byte trisb=0x86

#byte portc=0x07
#byte trisc=0x87

#bit motor=0x07.1

#byte portd=0x08
#byte trisd=0x88

#byte porte=0x09
#byte trise=0x89

#byte tmr0=0x01
#byte option_reg=0x81
#byte intcon=0x0b

#byte tmr1h=0x0f
#byte tmr1l=0x0e
#byte t1con=0x10
#byte pir1=0x0c
#byte pie1=0x8c

#bit tmr1on=t1con.0

#bit tmr0ie=intcon.5
#bit tmr0if=intcon.2

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

void display_sec(int n);
void display_mint(int q);
void gsm(unsigned char no);
void display(int m);
unsigned int x[2]={0,0},y[3]={0,0},v[2]={0,0};
int16 count=0,dummy=0;
int a[3]={0},b=0,sec=0,mint=0;
int1 flag=0;

#int_timer0
timer0_isr()
{
b++;
if(b==43)
{
b=0;
sec++;
}
if(sec==60)
{
sec=0;
mint++;
}
if(mint==60)
{
mint=0;
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
portb=0x00;portc=0x00;portd=0x00;porte=0x00;porta=0x00;
trisb=0x00;trisc=0x01;trisd=0x00;trise=0x00;trisa=0x00;

t1con=0x07;
tmr1l=0x00;
tmr1h=0x00;

option_reg=0x07;
intcon=0xa0;
tmr0=0x00;
delay_ms(2);
command(0x38);
command(0x06);
command(0x0c);
command(0x01);

delay_ms(100);
command(0x80);
data("SPEED MONITORING:");
command(0xc0);
data("    SYSTEM    ");
delay_ms(2000);
command(0x01);

fputs("AT+CMGF=1");
delay_ms(1000);


fputs("AT+CNMI=1,2,0,0,0");
delay_ms(1000);

fputs("AT+CMGR=1");
delay_ms(1000);

while(1)
{
delay_ms(150);
command(0xc0);
data("SPEED:");
motor=1;
count=make16(tmr1h,tmr1l);
display(count);
delay_ms(200);
command(0x80);
data("MINT:SEC::");
display_sec(sec);
delay_ms(100);
display_mint(mint);

if(mint==1)
{
gsm(0);
}
}
}
void display(int m)
{
int j=0,i=0;
for(j=0;j<=1;j++)
{
y[j]=m%10;
a[i]=m%10;
m=m/10;
}
command(0xc7);
data(y[2]|0x30);
data(y[1]|0x30);
data(y[0]|0x30);
}
void display_mint(unsigned int q)
{
int s=0;
for(s=0;s<=1;s++)
{
v[s]=q%10;
q=q/10;
}
command(0xc8a);
data(v[1]|0x30);
data(v[0]|0x30);
data(":");
}
void display_sec(unsigned int n)
{
int i=0;
for(i=0;i<=1;i++)
{
x[i]=n%10;
n=n/10;
}
command(0x8d);
data(x[1]|0x30);
data(x[0]|0x30);
}

void gsm(unsigned char no)
{
int b;
if(no==0)
puts("AT+CMGS=\"8056308831\"");

puts("SPEED");
puts(a[2]|0x30);
puts(a[1]|0x30);
puts(a[0]|0x30);
putc(0x1a);

}
