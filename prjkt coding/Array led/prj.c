#INCLUDE<16F877A.H>
#USE DELAY(CLOCK=11059200)
#use rs232(baud=9600,parity=N,xmit=pin_C6,rcv=pin_C7)

#BYTE TRISA=0X85
#BYTE TRISB=0X86
#BYTE TRISC=0X87
#BYTE TRISD=0X88
#BYTE TRISE=0X89

#BYTE PORTA=0X05
#BYTE PORTB=0X06
#BYTE PORTC=0X07
#BYTE PORTD=0X08
#BYTE PORTE=0X09


///////////////////////
//////LCD PINS/////////
///////////////////////

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2


///////////////////////
//////LCD COMMANDS/////
///////////////////////
int16 READ_ADC(INT );
VOID DISPLAY_NUM(INT POS,INT16 NUM);
void gsm(unsigned char no);
VOID COMMAND(unsigned char com)
{
 PORTD=COM;
 reg=0;rw=0;
 en=1;delay_ms(1);en=0;
}

VOID DATA(unsigned char da)
{
portd=da;
reg=1;rw=0;
en=1;delay_ms(1);en=0;
}

void LCD_INT(void)
{
   command(0x38);
   delay_ms(10);
   command(0x06);
   delay_ms(10);
   command(0x0c);
   delay_ms(10);
   command(0x01);
   delay_ms(10);
}

INT R[26],I=0,LCD=0,J=0,CCD=0;
INT1 DISPLAY=0;
#INT_RDA
USART()
{
   R[I]=FGETC();
   
   I++;
   
   IF(I==25)
   {
      DISPLAY=1;
   }
}
  
VOID MAIN()
{

   TRISA=0X00;
   TRISB=0X00;
   TRISC=0X80;
   TRISD=0X00;
   TRISE=0X00;

   PORTA=0X00;
   PORTB=0X00;
   PORTC=0X00;
   PORTD=0X00;
   PORTE=0X00;


   LCD_INT();

   ENABLE_INTERRUPTS(GLOBAL);
   ENABLE_INTERRUPTS(INT_RDA);         /////    INBUILT FUNCTION TO ENABLE UART RECEPTION

   COMMAND(0X80);
   DATA("DISPALY");
   DELAY_MS(1000);
   COMMAND(0X01);
   LCD=0X8F;
   
   
   WHILE(1)
   {
      IF(DISPLAY==1)
      {
         DELAY_MS(200);
         command(0x01);
         LCD=LCD-0X01;
         CCD=LCD;

         FOR(J=0;J<26;J++)
         {
            COMMAND(CCD);
            DATA(R[J]);
            CCD++;
         }
         
         IF(LCD==0X77)
         {
            LCD=0X8F;
         }
        
      }
   }
}

