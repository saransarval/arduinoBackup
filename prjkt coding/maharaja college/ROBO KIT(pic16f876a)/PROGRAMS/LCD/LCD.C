///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////////// ************* GRT EMBEDDED SOLUITIONS ************ /////////////
//***************************************************************************//
             //THIS PROGRAM IS DEVELOPED USING CCS COMPILER DEMO VERSION//
//***************************************************************************///
////////////////////////////////////////////////////////////////////////////////


#INCLUDE<16F876A.H>                          ////////////// HEADER FILE/////////
#USE DELAY(CLOCK=11059200)                   /// DELAY FUNCTION (PRE DEFINED) //


////////////////////////////////////////////////
////////////////////////////////////////////////
///////  REFERING THE REGISTER ADDRESS /////////
////////////////////////////////////////////////
////////////////////////////////////////////////

#BYTE TRISA=0X85
#BYTE TRISB=0X86
#BYTE TRISC=0X87

#BYTE PORTA=0X05
#BYTE PORTB=0X06
#BYTE PORTC=0X07

#INCLUDE<LCD.H>                        /// INCLUDE THIS HEADER IN  THE PROJECT FILE TO BE CREATED
////////////////////////////////////////////////
////////////////////////////////////////////////
///////          MAIN PROGRAM          /////////
////////////////////////////////////////////////
////////////////////////////////////////////////


VOID MAIN()
{
         //76543210// RESPECTIVE PINS IN THE PORT// 0B REFERS TO BINARY// 0X REFERS TO HEX
   TRISC=0B00000000;                      ///  HERE ALL PINS ARE MADE TO OPERATE AS  O/P
   PORTC=0B00000000;                      // INITILAL STATUS OF PIN IS MADE TO BE 0
   
   
   lcd_init();
   DELAY_MS(100);
   LCD_PUTC("GRT WELCOMES U");
   WHILE(1)
   {

   }
   
   
}
