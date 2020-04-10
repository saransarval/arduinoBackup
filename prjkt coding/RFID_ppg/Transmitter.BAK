#include <16F877A.h>
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_c6,rcv=PIN_c7)
#include<lcd.h>
#byte portb=0x06
#byte trisb=0x86
#byte porta=0x05
#byte trisa=0x85
#byte portc=0x07
#byte trisc=0x87

#byte intcon=0x0b
#byte pie1=0x8c
#byte pir1=0x0c
#byte rcsta=0x18
#byte txsta=0x98
#byte spbrg=0x99

#bit key1=portb.1
#bit key2=portb.2
#bit key3=portb.3
#bit key4=portb.4

#bit relay1=porta.0
#bit relay2=porta.1
#bit relay3=porta.2
#bit relay4=porta.3

#byte rcreg=0x1a
#byte txreg=0x19


char a[12]={0,0,0,0,0,0,0,0,0,0,0},i=0;
int r=0, s=0, flag=0,b=0,c=0;
int1 glag=0;

#int_RDA
RDA_isr()
{
a[i]=fgetc();
i++;
if(i==12)
{
i=0;
glag=1;
}
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

   lcd_init();

   //intcon=0x00;
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



  /*
   command(0xc0);
   data(a[0]);
   data(a[1]);
   data(a[2]);
   data(a[3]);
   data(a[4]);
   data(a[5]);
   data(a[6]);
   data(a[7]);
   data(a[8]);
   data(a[9]);
   data(a[10]);
   data(a[11]);
   //glag=0;



r=a[10] -'0';
s=a[11] - '0';


   if(r==6 && s==5)
   {
 command(0x80);
 data("****WELCOME****");
 */
 }
}
