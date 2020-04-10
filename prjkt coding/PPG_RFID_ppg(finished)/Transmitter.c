#include <16F877A.h>
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_c6,rcv=PIN_c7)

#byte porta=0x05
#byte trisa=0x85

#byte portb=0x06
#byte trisb=0x86

#byte portc=0x07
#byte trisc=0x87

#byte portd=0x08
#byte trisd=0x88

#byte porte=0x09
#byte trise=0x89

#byte intcon=0x0b
#byte pie1=0x8c
#byte pir1=0x0c
#byte rcsta=0x18
#byte txsta=0x98
#byte spbrg=0x99

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

#byte rcreg=0x1a
#byte txreg=0x19


char a[12],i=0,j=0;
int r=0, s=0, flag=0,b=0,c=0;
int1 glag=0,glag_1=0,receiver=0;

#int_RDA
RDA_isr()
{
if(receiver==0)
{
a[i]=fgetc();
i++;
if(i==4)
{
i=0;
glag=1;
}
}
if(receiver==1)
{
a[i]=fgetc();
i++;
if(i==12)
{
i=0;
glag_1=1;
}
}
}
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
void main()
{
   //portb=0x00;
   //trisb=0x1e;
   //porta=0x00;
   //trisa=0x00;
   portd=0x00;
   trisd=0x00;
   trise=0x00;
	portc=0x00;
	trisc=0x80;

fputs("AT+CMGF=1");
delay_ms(1000);


fputs("AT+CNMI=1,2,0,0,0");
delay_ms(1000);

fputs("AT+CMGR=1");
delay_ms(1000);  //intcon=0x00;
   //pie1=0x20;
   //rcreg=0x00;
   //setup_timer_2(T2_DIV_BY_1,255,1);
	//setup_ccp1(CCP_PWM);

   enable_interrupts(global);
   enable_interrupts(int_rda);
   fputc(a[i]);
   command(0x01);
   command(0x80);

   delay_ms(1);
   i=0;
   data("RFID TAG");



   while(1)
   {

   if(glag==1)
   {
   command(0xc0);

      for(i=0;i<12;i++)
      {
         data(a[i]|0x30);
      }

      delay_ms(200);

      if(a[10]=='5' && a[11]=='D')
      {
      fputs("S1");
      command(0x80);
      data("   TAG FIRST   ");
      command(0xc0);
      data(" PATIENT1 RAJA ");
      b=1;
      delay_ms(250);
      if(b==1)
        {
            command(0xc0);
            data("  PATIENT1 RAJA ");
            delay_ms(2000);
            command(0x80);
            data("  PATIENT1 RAJA ");
            command(0xc0);
            data("DOCTOR THANGAM");
            delay_ms(2000);
            command(0x80);
            data("DOCTOR THANGAM");
            command(0xc0);
            data(" DISEASE  COLD  ");
            delay_ms(2000);
            command(0x80);
            data(" DISEASE  COLD  ");
            command(0xc0);
            data(" PRESCRIPTION  ");
            delay_ms(2000);
            command(0x80);
            data(" PRESCRIPTION  ");
            command(0xc0);
            data(" EXCEDRIN TAB ");
            b=0;
          }


      }
      else if(a[10]=='3' && a[11]=='E')
      {
      fputs("S2");
      command(0x80);
      data("  TAG SECOND  ");
      command(0xc0);
      data("PATIENT2 YUVARAJ");
      c=1;
      delay_ms(150);
      if(c==1)
      command(0xc0);
            data("PATIENT2 YUVARAJ");
            delay_ms(2000);
            command(0x80);
            data("PATIENT2 YUVARAJ");
            command(0xc0);
            data("DOCTOR THANGAM");
            delay_ms(2000);
            command(0x80);
            data("DOCTOR THANGAM");
            command(0xc0);
            data(" DISEASE FEVER ");
            delay_ms(2000);
            command(0x80);
            data(" DISEASE FEVER");
            command(0xc0);
            data(" PRESCRIPTION  ");
            delay_ms(2000);
            command(0x80);
            data(" PRESCRIPTION  ");
            command(0xc0);
            data("PREVACID SOLUT");
            c=0;
      }

      glag=0;i=0;
   }

 }
}
