#include <16F877A.h>
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_c6,rcv=PIN_c7, bits = 8, errors, stream=bus)
#use rs232(baud=9600, xmit=PIN_c3,rcv=PIN_c4, bits = 8, errors, stream=bus2)

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

#byte tmr0=0x01
#byte option_reg=0x81
#byte intcon=0x0b
#byte pie1=0x8c
#byte pir1=0x0c
#byte rcsta=0x18
#byte txsta=0x98
#byte spbrg=0x99

#bit key=portb.0
#bit tmr0ie=0x0b.5

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2
#bit RELAY = portb.1

#byte rcreg=0x1a
#byte txreg=0x19

char a[12],i=0,j=0;
int r=0, s=0, flag=0,b=0,c=0,m=0,count=0,sec=0,mint=0;
int1 glag=0,glag_1=0,receiver=0,x=0,y=1;
void display(unsigned int o);
void display1(unsigned int p);
void gsm(unsigned char no);
void gsm1(unsigned char no);
void gsm2(unsigned char no);

#int_RDA
RDA_isr()
{
   if(receiver==0)
  {
   a[4]=a[3];
   a[3]=a[2];
   a[2]=a[1];
   a[1]=a[0];
   a[0]=fgetc();
   glag=1;
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

#int_timer0
timer0_isr()
{
   count++;
   if(count==43)
  {
   count=0;
   sec++;
  }
   if(sec==59)
  {
   sec=0;
   mint++;
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
         porta=0x00;
         trisa=0x00;
         portb=0x00;
         trisb=0x01;
         portd=0x00;
         trisd=0x00;
         trise=0x00;
      	portc=0x00;
      	trisc=0x80;

         option_reg=0x07;
         intcon=0xc0;
         tmr0=0x00;
         delay_ms(20);

         command(0x38);
         command(0x06);
         command(0x0c);
         
         command(0x80);
         data("PATIENT MONITORING");
         command(0xc0);
         data("    SYSTEM     ");

         delay_ms(4000);
         command(0x01);

         fputs("AT+CMGF=1", bus);
         delay_ms(1000);


         fputs("AT+CNMI=1,2,0,0,0", bus);
         delay_ms(1000);

         fputs("AT+CMGR=1", bus);
         delay_ms(1000);

         enable_interrupts(global);
         enable_interrupts(int_rda);
      //fputc(a[i]);
         tmr0ie=1;

while(1)
{
      display(sec);
      display1(mint);

if((sec>=10) && (y==1))
   {
      tmr0ie=0;
      //RELAY=0;
      y=0;
      sec=0;
      //delay_ms(1000);
      gsm(0);
      delay_ms(1000);
      gsm(1);
      delay_ms(1000);
   }

if(glag==1)
   {
      if((a[0]=='G') && (a[1]=='N') && (a[2]=='I') && (a[3]=='R'))
   {
      tmr0ie=1;
      a[0]=0;

   }
if((key==0) && (mint<1))
  {
      RELAY = 1;
      x=0;mint=0;sec=0;count=0;
      command(0x80);
      data("Doctor is Now");
      command(0xc0);
      data(" Avilable   ");
      //delay_ms(100);
      gsm1(0);
      delay_ms(1000);
      gsm1(1);
      delay_ms(1000);
      receiver=1;tmr0ie=0;glag=0;

  }
if((mint>=1) && (key==1))
  {
      RELAY = 0;
      x=1;mint=0;sec=0;count=0;
      command(0x80);
      data("Doctor is Not");
      command(0xc0);
      data(" Avilable   ");
      //delay_ms(100);
      gsm2(0);
      delay_ms(1000);
      gsm2(1);
      delay_ms(1000);
      receiver=0;tmr0ie=0;glag=0;

  }
}

if(glag_1==1)
   {
      if(a[10]=='5' && a[11]=='D')
   {
      glag=0;m=0;
      puts("S1",bus2);
      command(0x80);
      data("   TAG FIRST   ");
      command(0xc0);
      data(" PATIENT1 RAJA ");
      b=1;
      delay_ms(100);
   if(b==1)
   {
      command(0xc0);
      data("  PATIENT1 RAJA ");
      delay_ms(1000);
      command(0x80);
      data("  PATIENT1 RAJA ");
      command(0xc0);
      data("DR. THANGAVELU");
      delay_ms(1000);
      command(0x80);
      data("DR. THANGAVELU");
      command(0xc0);
      data("HOSPITAL NAME");
      delay_ms(1000);     
      command(0x80);
      data("HOSPITAL NAME");
      command(0xc0);
      data("  ASHWIN  ");
      delay_ms(1000);
      command(0x80);
      data("  ASHWIN  ");
      command(0xc0);
      data("  AGE:24  ");
      delay_ms(1000);
      command(0x80);
      data("  AGE:24  ");
      command(0xc0);
      data(" HEIGHT: 5.2  ");
      delay_ms(1000);
      command(0x80);
      data(" HEIGHT: 5.2   ");
      command(0xc0);
      data(" WEIGHT: 50  ");
      delay_ms(1000);
      command(0x80);
      data(" HEIGHT: 5.2   ");
      command(0xc0);
      data(" BLOOD : O+  ");
      delay_ms(1000);
      command(0x80);
      data(" BLOOD: O+   ");
      command(0xc0);
      data(" DISEASE  COLD  ");
      delay_ms(1000);
      command(0x80);
      data(" DISEASE  COLD  ");
      command(0xc0);
      data(" PRESCRIPTION  ");
      delay_ms(1000);
      command(0x80);
      data(" PRESCRIPTION  ");
      command(0xc0);
      data(" EXCEDRIN TAB ");
      b=0;
  }


}
else if(a[10]=='3' && a[11]=='E')
  {
      puts("S2",bus2);
      command(0x80);
      data("  TAG SECOND  ");
      command(0xc0);
      data("PATIENT2 YUVARAJ");
      c=1;
      delay_ms(100);
if(c==1)
  {
      command(0xc0);
      data("PATIENT2 YUVARAJ");
      delay_ms(1000);
      command(0x80);
      data("PATIENT2 YUVARAJ");
      command(0xc0);
      data("DR. THANGAVELU");
      delay_ms(1000);
      command(0x80);
      data("DR. THANGAVELU");
      command(0xc0);
      data("HOSPITAL NAME");
      delay_ms(1000);     
      command(0x80);
      data("HOSPITAL NAME");
      command(0xc0);
      data("  ASHWIN  ");
      delay_ms(1000);
      command(0x80);
      data("  ASHWIN  ");
      command(0xc0);
      data("  AGE:21  ");
      delay_ms(1000);
      command(0x80);
      data("  AGE:21  ");
      command(0xc0);
      data(" HEIGHT: 5.5  ");
      delay_ms(1000);
      command(0x80);
      data(" HEIGHT: 5.5   ");
      command(0xc0);
      data(" WEIGHT: 55  ");
      delay_ms(1000);
      command(0x80);
      data(" HEIGHT: 5.5   ");
      command(0xc0);
      data(" BLOOD : B+  ");
      delay_ms(1000);
      command(0x80);
      data(" BLOOD: B+   ");
      command(0xc0);
      data(" DISEASE FEVER ");
      delay_ms(1000);
      command(0x80);
      data(" DISEASE FEVER");
      command(0xc0);
      data(" PRESCRIPTION  ");
      delay_ms(1000);
      command(0x80);
      data(" PRESCRIPTION  ");
      command(0xc0);
      data("PREVACID SOLUT");
      delay_ms(1000);
      c=0;
  }
}
glag_1=0;i=0;
}
}
}

void display(unsigned int o)
{
      int z[2],j;
      for(j=0;j<=1;j++)
      {
      z[j]=o%10;
      o=o/10;
      }
      command(0xce);
      data(z[1]|0x30);
      data(z[0]|0x30);
}
void display1(unsigned int p)
{
      int y[2],k;
      for(k=0;k<=1;k++)
      {
      y[k]=p%10;
      p=p/10;
      }
      command(0xcb);
      data(y[1]|0x30);
      data(y[0]|0x30);
      data(":");
}
void gsm(unsigned char no)
{
      if(no==0)
      {
      puts("AT+CMGS=\"9943656814\"", bus);
      puts("TODAY IS RAJA TREATMENT DAY BY ASWIN HOSPITAL", bus);
      putc(0x1a, bus);
      }

      else
      {
      puts("AT+CMGS=\"8940611298\"", bus);
      puts("TODAY IS UVARAJ TREATMENT DAY BY ASWIN HOSPITAL", bus);
      putc(0x1a, bus);

      }


}
void gsm1(unsigned char no)
{
      if(no==0)
      {
      puts("AT+CMGS=\"9943656814\"", bus);
      puts("DOCTOR IS NOW AVILABLE", bus);
      putc(0x1a, bus);
      }
      else
      {
      puts("AT+CMGS=\"8940611298\"", bus);
      puts("DOCTOR IS NOW AVILABLE", bus);
      putc(0x1a, bus);
      }
     
}
void gsm2(unsigned char no)
{
      if(no==0)
      {
      puts("AT+CMGS=\"9943656814\"", bus);
      puts("DOCTOR IS NOT AVILABLE", bus);
      putc(0x1a, bus);
      }
      else
      {
      puts("AT+CMGS=\"8940611298\"", bus);
      puts("DOCTOR IS NOT AVILABLE", bus);
      putc(0x1a, bus);
      }
     
}
