#INCLUDE<16F876A.H>
#USE DELAY(CLOCK=11059200)

#BYTE TRISA=0X85
#BYTE TRISB=0X86
#BYTE TRISC=0X87

#BYTE PORTA=0X05
#BYTE PORTB=0X06
#BYTE PORTC=0X07

#BYTE OPTION_REG=0X81
#byte intcon=0x0b


#BIT REG=PORTc.4
#BIT E=PORTc.5

#BIT LED=PORTB.0
#BIT BUZ=PORTB.3
#BIT KEY1=PORTB.1
#BIT KEY2=PORTB.2

#BIT IR1=PORTB.6
#BIT IR2=PORTB.5

#BIT OBJ_DET=PORTB.7

#BIT MOT1=PORTA.1
#BIT MOT2=PORTA.3


void command(unsigned int com)
{

	portc=com>>4;
	//REG=0;
	E=1;
	delay_MS(5);
	E=0;

	PORTC=com;
	REG=0;
	E=1;
	delay_MS(5);
	E=0;



}

void data(unsigned int da)
{

	portc=da>>4;
	//REG=1;
	E=1;
	delay_MS(5);
	E=0;

	PORTC=da;
	REG=1;
	E=1;
	delay_MS(5);
	E=0;

}
int1 slag1=0,slag2=0,always=0,OBJ=0;
/*
#INT_RB
PORT_CHANGE_INT()
{


   IF(OBJ_DET==0)
   {
      OBJ=1;
   }

   always=0;
}
*/

VOID MAIN()
{
   TRISA=0X00;
   TRISB=0Xf6;
   TRISC=0X00;

   PORTA=0X00;
   PORTB=0X00;
   PORTC=0X00;

   OPTION_REG=0X00;
   INTCON=0X88;

   COMMAND(0X02);
   command(0x28); // set function 4 bit, 2 line, 5*7
   command(0x06); // entry mode  3bit high,   increment cursor move direction, display shift
   command(0x0c); // display on  4 bit high, display on, no curson, no blinking
   command(0x01); // clear

   DELAY_MS(100);
   command(0x80);DELAY_MS(1);
   data("GRT WELCOMES ");
   COMMAND(0XC0);DELAY_MS(1);
   DATA("YOU ALL");
   delay_ms(1000);
	always=1;
  // MOT1=1;DELAY_MS(3000);MOT1=0;led=1;
  // MOT2=1;DELAY_MS(3000);MOT2=0;led=0;

   WHILE(1)
   {

		always=1;

      IF(OBJ_DET==1)
      {
      MOT1=0;MOT2=0;LED=1;BUZ=1;DELAY_MS(1000);LED=0;BUZ=0;ALWAYS=0;OBJ=0;
      }
         


		if(always==1)
		{
		MOT1=1;MOT2=1;OBJ=0;
		}


   }
}

