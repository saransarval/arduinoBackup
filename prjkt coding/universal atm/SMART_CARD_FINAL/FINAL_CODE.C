#include <16F877A.h>
#use delay(clock=11059200)
#use rs232(baud=9600, xmit=PIN_c6,rcv=PIN_c7, bits=8, errors)
#fuses NOWDT, HS, PUT, NOPROTECT, NOBROWNOUT, NOLVP, NOCPD, NOWRT

#byte trisb=0x86
#byte portb=0x06

#byte trisd=0x88
#byte portd=0x08

#byte trisc=0x87
#byte portc=0x07

#bit RELAY = portc.0

#byte trise=0x89
#byte porte=0x09

#byte intcon=0x0b
#byte option_reg=0x81
#byte rcreg=0x1a

#bit c1=portb.7
#bit c2=portb.6
#bit c3=portb.5
#bit c4=portb.4

#bit r4=portb.0
#bit r3=portb.1
#bit r2=portb.2
#bit r1=portb.3

#bit reg=porte.0
#bit rw=porte.1
#bit en=porte.2

#define Z PUTC('M')
#define Y PUTC('L')

unsigned int16 enter_amt = 0 , total_amt = 0 , amount = 0 , total_no[5]={0} , w[5] = {0};
unsigned char a[12]={0,0,0,0,0,0,0,0,0,0,0,0} , x=0, i=0, i1=0 ;
unsigned int1 id_flag=0,flag_1=1,glag=0,glag_1=0,glag_2=0,glag_3=0,glag_4=0,k=0,l=0,m=1,n=1,p=1,o=1,t=0,q=1,r=0, s=0 ,receiver=0,c=0,rb_flag=0 , amt_flag=0 , id = 0 ;
void display(unsigned int16 m);

#int_rb
rb_isr()
{
      portb=0xf0;
      r1=0; if(c1==0) {x=0;} if(c2==0){x=1;} if(c3==0){x=2;} if(c4==0){x=3;}r1=1;

      r2=0; if(c1==0) {x=4; }if(c2==0){x=5;} if(c3==0){x=6;} if(c4==0){x=7;}r2=1;

      r3=0; if(c1==0) {x=8;} if(c2==0){x='A';} if(c3==0){x='B';} if(c4==0){x='C';}r3=1;

      r4=0; if(c1==0) {x='D';} if(c2==0){x='E';} if(c3==0){x='F';} if(c4==0){x='G';}r4=1;
      portb=0x00;
      while(!(portb==0xf0));
      rb_flag=1;
      delay_ms(2);
}

#int_rda
rda_isr()
{
      if(id==0)
        {
         a[i1]=fgetc();
         i1++;
            if(i1>=5)
             {
               i1=0;
               amt_flag=1;
             }
        }
      if(id==1)
      {
         a[i1]=fgetc();
         i1++;
            if(i1>=12)
             {
               i1=0;
               id_flag=1;
             }
      }
}
void command(unsigned int com)
{
      portd=com;
      reg=0;
      rw=0;
      en=1;
      delay_us(50);
      en=0;
}
void data(unsigned int dat)
{
      portd=dat;
      reg=1;
      rw=0;
      en=1;
      delay_us(50);
      en=0;
}

void main()
{
      int t,r,c;

      trisb=0xf0;
      portb=0x00;

      trisd=0x00;
      portd=0x00;

      trisc=0x80;
      portc=0x00;

      trise=0x00;
      porte=0x00;

      option_reg=0x00;
      intcon=0xc8;

      enable_interrupts(global);
      enable_interrupts(int_rda);

      command(0x38);
      command(0x0c);
      command(0x06);
      command(0x01);

      delay_ms(2);

      command(0x80);
      data("   PLEASE ENTER  ");
      command(0xc0);
      data("   YOUR CHOICES    ");
      delay_ms(500);
      command(0x01);
      delay_ms(2);
      putc('1');

while(1)
{
if(amt_flag==1)
{
      RELAY = 0;
      s=1;
      amt_flag=0;
      command(0x01);
      delay_ms(2);

      total_amt = 0;
      total_amt += (a[0]-'0')*10000;
      total_amt += (a[1]-'0')*1000;
      total_amt += (a[2]-'0')*100;
      total_amt += (a[3]-'0')*10;
      total_amt += (a[4]-'0')*1;

      id=1;
}
if((x==0) && (o==1))
{
      s=0;
      k=1;
      command(0x80);
      data("K.A:");
      command(0x84);
      data("CLASS ROOM");
      delay_ms(1);
      command(0xc0);
      data("K.B:");
      command(0xc4);
      data("LIBRARY");
      delay_ms(1);
      command(0x94);
      data("K.C:");
      command(0x98);
      data("CANTEEN");
      delay_ms(1);
      command(0xd4);
      data("K.D:");
      command(0xd8);
      data("HOSTEL");
      delay_ms(1);
      command(0xdf);
      data("K.E:");
      command(0xe3);
      data("BANKS");

      RELAY=1;
}
if((x=='A') && (k==1))                                              ////// CLASS ROOM
{
      x=0;o=0;glag=1;glag_2=0;glag_1=0;glag_3=0;glag_4=0;
      putc('A');
      command(0x01);
      delay_ms(2);
      command(0x80);
      data("CLASS ROOM:");
      delay_ms(100);

            }
               if((id_flag==1) && (glag==1))
               {
                  if((a[10]=='5') && (a[11]=='1'))
                  {
                           receiver=1;o=0;
                           Z;
                           command(0x80);
                           data("DIVYA IS PRESENT");
                                 }
                                    if((a[9]=='5') && (a[10]=='3'))
                                    {
                                       receiver=0;o=0;
                                       Y;
                                       command(0xc0);
                                       data("RAMYA IS PRESENT");
                                          }
                                             id_flag=0;

               }

if(x=='B')                                                            ////// LIBRARY
{
         x=0;o=0;glag=0;glag_2=0;glag_1=1;glag_3=0;glag_4=0;
         putc('B');
         command(0x01);
         command(0x80);
         delay_ms(2);
         data("LIBRARY:");
         delay_ms(100);

}
                 if((id_flag==1) && (glag_1==1))
                  {
                     if((a[10]=='5') && (a[11]=='1'))
                     {
                              o=0;l=1;
                              Z;
                              command(0x80);
                              data("DUES:RS.100");
                              command(0xc0);
                              data("WANT TO PAY");
                              command(0x94);

                               }
                                  if((a[9]=='5') && (a[10]=='3'))
                                  {
                                       l=0;o=0;
                                       Y;
                                       command(0x80);
                                       data("  NO DUES  ");
                                       command(0xc0);
                                       data("AMOUNT PAID");
                                        }
                                           id_flag=0;
                }
if(x=='C')                                                           ////// CANTEEN
{
         x=0;o=0;glag_1=0;glag=0;glag_2=1;glag_3=0;glag_4=0;
         putc('C');
         command(0x01);
         delay_ms(2);
         command(0x80);
         data("CANTEEN:");
         delay_ms(100);

}
                if((id_flag==1) && (glag_2==1))
                 {
                    if((a[10]=='5') && (a[11]=='1'))
                    {
                           m=1;o=0;
                           Z;
                           putc('@');
                           putc('M');
                           command(0x80);
                           data("AMOUNT PAID");
                           command(0xc0);
                           data("BY DIVYA");

                               }
                                  if((a[9]=='5') && (a[10]=='3'))
                                  {
                                       m=0;o=0;
                                       Y;
                                       putc('@');
                                       putc('L');
                                       command(0x80);
                                       data("AMOUNT PAID");
                                       command(0xc0);
                                       data("BY RAMYA");
                                               }
                                                 id_flag=0;
                 }
if(x=='D')                                                           /////// HOSTEL
{
            x=0;o=0;glag=0;glag_1=0;glag_2=0;glag_4=0;glag_3=1;
            putc('D');
            command(0x01);
            delay_ms(2);
            command(0x80);
            data("HOSTEL:");
            delay_ms(100);

}
               if((id_flag==1) && (glag_3==1))
                  {
                     if((a[10]=='5') && (a[11]=='1'))
                     {
                           n=1;o=0;
                           Z;
                           command(0x80);
                           data("AMOUNT PAID");
                           command(0xc0);
                           data("BY DIVYA");
                               }
                                  if((a[9]=='5') && (a[10]=='3'))
                                   {
                                       n=0;o=0;
                                       Y;
                                       command(0x80);
                                       data("AMOUNT PAID");
                                       command(0xc0);
                                       data("BY RAMYA");
                                             }
                                                 id_flag=0;
                 }

if(x=='E')                                                              ////// BANKS
{
         x=0;o=0;glag_4=1;glag_3=0;glag_2=0;glag_1=0;glag=0;
         putc('E');
         command(0x01);
         delay_ms(2);
         command(0x80);
         data("BANKS:");
         command(0x86);
         data("HDFC-K.7");
         command(0xc0);
         data("SBI-K.8");
         command(0x94);
         data("IB-K.9");
         command(0xd4);

}
if((x==6) && (glag_4==1))
{
         t=1;glag_4=0;
         command(0x01);
         command(0x80);
         putc('J');
         data("HDFC BANK HAS BEEN   ");
         command(0xc0);
         data("     SELECTED    ");
         delay_ms(2);
         RELAY=1;
}
else if((x==7) && (glag_4==1))
{
         t=1;glag_4=0;
         command(0x01);
         putc('K');
         command(0x80);
         data("SBI BANK HAS BEEN   ");
         command(0xc0);
         data("     SELECTED    ");
         delay_ms(2);
         RELAY=1;
}
else if((x==8) && (glag_4==1))
{
         t=1;glag_4=0;
         command(0x01);
         putc('O');
         command(0x80);
         data("IB BANK HAS BEEN   ");
         command(0xc0);
         data("     SELECTED    ");
         delay_ms(2);
         RELAY=1;
}
   if((id_flag==1) && ( t==1))
      {

        if((a[10]=='5') && (a[11]=='1'))
              {
         t=0;x=0;p=0;id_flag=0;glag_4=0;r=1;id=0;
         Z;
         command(0x01);
         command(0x80);
         data("CASH WITHDRA-K.F");
         command(0xc0);
         data("CASH DEPOS-K.G");
              }
        else if((a[9]=='5') && (a[10]=='3'))
           {
         t=0;x=0;p=0;id_flag=0;glag_4=0;c=1;id=0;
         Y;
         command(0x01);
         command(0x80);
         data("CASH WITHDRA-K.F");
         command(0xc0);
         data("CASH DEPOS-K.G");
                          }
     }
if((x=='F') && (r==1))
{
         x=0;r=0;
         putc('@');
         putc('M');
         delay_ms(2);
         command(0x01);
         command(0x80);
         data("CASH WITHDRAWAL  ");
         command(0xc0);
         data("BALANCE AMOUNT:");
         display(total_amt);

}
else if((x=='G') && (r==1))
{
         x=0;r=0;
         putc('*');
         putc('M');
         delay_ms(2);
         command(0x01);
         command(0x80);
         data("CASH DEPOSITED ");
         command(0xc0);
         data("TOTAL AMOUNT:");
         display(total_amt);
}

if((x=='F') && (c==1))
{
         x=0;c=0;
         putc('@');
         putc('L');
         delay_ms(2);
         command(0x01);
         command(0x80);
         data("CASH WITHDRAWAL  ");
         command(0xc0);
         data("BALANCE AMOUNT:");
         display(total_amt);
}
else if((x=='G') && (c==1))
{
         x=0;c=0;
         putc('*');
         putc('L');
         delay_ms(2);
         command(0x01);
         command(0x80);
         data("CASH DEPOSITED ");
         command(0xc0);
         data("TOTAL AMOUNT:");
         display(total_amt);
}
}
}
void display(unsigned int16 m)
{
      int u ;

      for(u=0;u<=4;u++)
      {
         w[u] = m%10;
         m = m/10;
      }
      data(w[4]|0x30);
      data(w[3]|0x30);
      data(w[2]|0x30);
      data(w[1]|0x30);
      data(w[0]|0x30);
}
