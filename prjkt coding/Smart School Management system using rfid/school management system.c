#include<16f877a.h>
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_c6,rcv=PIN_c7)

#byte trisa=0x85
#byte porta=0x05

#byte trisc=0x87
#byte portc=0x07

#byte trisd=0x88
#byte portd=0x08

#byte trise=0x89
#byte porte=0x09

#byte intcon=0x0b
#byte rcreg=0x1a

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

char i=0, a[12]={0,0,0,0,0,0,0,0,0,0,0,0};
int1 flag=0;
void function(int16);
void gsm(unsigned int no);
void gsm1(unsigned int no);

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

#int_rda
rda_isr()
{
      a[i]=fgetc();
      i++;
   if(i==12)
    {
      i=0;
      flag=1;
    }
}


void main()
{

   trisa=0x00;
   porta=0x00;
   trisc=0x80;
   portc=0x00;
   trisd=0x00;
   portd=0x00;
   trise=0x00;
   porte=0x00;
   
   
   fputs("AT+CMGF=1");
   delay_ms(1000);
   
   fputs("AT+CNMI=1,2,0,0,0");
   delay_ms(1000);
   
   fputs("AT+CMGR=1");
   delay_ms(1000);
   
   
   command(0x38);
   command(0x06);
   command(0x0c);
   command(0x01);
   
   command(0x80);
   data("Hi GRT");
   
   enable_interrupts(global);
   enable_interrupts(int_rda);
   command(0x01);
   command(0x80);
   
   delay_ms(1000);
   i=0;
   data("RFID TAG");

while(1)
{
if(flag==1)
{
if(a[10]=='E' && a[11]=='0')
{
   command(0x80);
   data("MANAGE SYSTEM");
   command(0xc0);
   data("PRIYA IS PRESENT");
   gsm(0);
   delay_ms(3000);
   gsm(1);
}
else if(a[10]=='8' && a[11]=='A')
{
   command(0x80);
   data("MANAGE SYSTEM");
   command(0xc0);
   data("ARCHANA IS PRESENT");
   gsm1(0);
   delay_ms(3000);
   gsm1(1);
}
i=0;flag=0;

}
}

}
void gsm(unsigned char no)
{
   if(no==0)
   puts("AT+CMGS=\"9750375234\"");
   else
   puts("AT+CMGS=\"9976077338\"");
   
   puts("PRIYA IS PRESENT");
   putc(0x1a);
}

void gsm1(unsigned char no)
{
   if(no==0)
   puts("AT+CMGS=\"9750375234\"");
   else
   puts("AT+CMGS=\"9976077338\"");
   
   puts("ARCHANA IS PRESENT");
   putc(0x1a);
}
