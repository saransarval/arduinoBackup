#include<16f877a.h>
#device adc=10
#use delay(clock=11059200)


#byte porte=0x09
#byte portd=0x08
#byte portc=0x07
#byte portb=0x06
#byte porta=0x05

#byte trisa=0x85
#byte trisb=0x86
#byte trisc=0x87
#byte trisd=0x88
#byte trise=0x89

#byte intcon=0x0b
#byte tmr0=0x01
#byte option_reg=0x81

#byte adcon0=0x1f
#byte adcon1=0x9f

#byte adresh=0x1e
#byte adresl=0x9e

#bit go=0x1f.2

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

#bit driver1=portb.0
#bit driver2=portb.1
#bit driver3=portb.2
#bit driver4=portb.3

#bit LDR1=portb.4
#bit LDR2=portb.5
#bit LDR3=portb.6
#bit LDR4=portb.7

#bit relay1=0x07.0
#bit relay2=0x07.1
/*#bit relay3=0x07.2
#bit relay4=0x07.3
#bit relay5=0x07.4
#bit relay6=0x07.5
#bit relay7=0x07.6
#bit relay8=0x07.7*/

#bit Battery_1=portc.4
#bit Battery_2=portc.5

int b=0,sec=0,mint=0,hrs=0;
unsigned int flag1, flag2, flag3, flag4;
unsigned int16 SOLAR=0,BATTERY=0;
int1 glag=0;
void display_solar(unsigned int m);
void display_battery(unsigned int o);
void command(unsigned char com);
void data(unsigned char da);

#int_rb
rb_isr()
{
if(LDR1==1 && LDR2==0 && flag1==0)
{
command(0x80);
data("X-AXIS A-CLOCKWISE");
driver1=1;
delay_ms(2000);
driver1=0;
flag1=1;
flag2=0;
command(0x01);
}
else
driver1=0;

if(LDR2==1 && LDR1==0 && flag2==0)
{
command(0x80);
data("X-AXIS CLOCKWISE");
driver2=1;
delay_ms(2000);
driver2=0;
flag2=1;
flag1=0;
command(0x01);
}
else
driver2=0;

if(LDR3==1 && LDR4==0 && flag3==0)
{
command(0x80);
data("Y-AXIS CLOCKWISE");
driver3=1;
delay_ms(2000);
driver3=0;
flag3=1;
flag4=0;
command(0x01);
}
else
driver3=0;

if(LDR4==1 && LDR3==0 && flag4==0)
{
command(0x80);
data("Y-AXIS A-CLOCKWISE");
driver4=1;
delay_ms(2000);
driver4=0;
flag4=1;
flag3=0;
command(0x01);
}
else
driver4=0;
}

#int_timer0
timer0_isr()
{
b++;
if(b==43)
{
b=0;
sec++;
if(sec==60)
{
sec=0;
mint++;
if(mint==60)
{
mint=0;sec=0;hrs++;
glag=1;
}
}
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
portd=0x00;
porte=0x00;
porta=0x00;
portc=0x00;
portb=0x00;

trisd=0x00;
trise=0x00;
trisa=0x3f;
trisc=0x00;
trisb=0xf0;

adresh=0x00;
adresl=0x00;
adcon1=0x82;

tmr0=0x00;
option_reg=0x07;
intcon=0x88;

command(0x38);
command(0x06);
command(0x0c);

delay_ms(300);
command(0x80);
data("SOLAR TRACKING");
delay_ms(1000);
command(0x01);

while(1)
{
delay_ms(10);
adcon0=0x81;
go=1;
while(go==1);
SOLAR=make16(adresh,adresl);

command(0x80);
data("SOLAR:");
display_solar(SOLAR);

delay_ms(100);
adcon0=0x89;
go=1;
while(go==1);
BATTERY=make16(adresh,adresl);

command(0xc0);
data("BATTERY:");
display_battery(BATTERY);
delay_ms(300);

if((SOLAR+50)>BATTERY)
{
relay1=1;relay3=1;relay5=1;relay7=1;relay2=0;relay4=0;relay6=0;relay8=0;
}
if((BATTERY+50)>SOLAR)
{
relay2=1;relay4=1;relay6=1;relay8=1;relay1=0;relay3=0;relay5=0;relay7=0;
}
}
}
void display_solar(unsigned int m)
{
int a[2],i=0;
for(i=0;i<=1;i++)
{
a[i]=m%10;
m=m/10;
}

command(0xc8);
data(a[1]|0x30);
data(a[0]|0x30);
}

void display_battery(unsigned int o)
{
int b[2],j=0;
for(j=0;j<=1;j++)
{
b[j]=o%10;
o=o/10;
}
command(0x88);
data(b[1]|0x30);
data(b[0]|0x30);
}
