#include <18F458.h>
#device adc=10
#define sub_station_id 0x00
#include "pic18_f_reg.h"
#include "can-18xxx8_own.h"
#include "reg.h"


#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES HS                 	   //Resistor/Capacitor Osc
#FUSES NOPROTECT             	//Code not protected from reading
#FUSES NOPUT                 	//No Power Up Timer
#FUSES NOCPD                 	//No EE protection
#FUSES NODEBUG               	//No Debug mode for ICD
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                 	//Program memory not write protected
#FUSES NOWRTD                	//Data EEPROM not write protected
#FUSES NOWRTB                	//Boot block not write protected
#FUSES NOCPB                 	//No Boot Block code protection
#FUSES NOWRTC                	//configuration not registers write protected
#FUSES NOEBTR                	//Memory not protected from table reads
#FUSES NOEBTRB               	//Boot block not protected from table reads
#define LDR 600


#use delay(clock=11059200)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
/*
#byte portb=0Xf81
#byte trisb= 0Xf93

#byte portc=0Xf82
#byte trisc= 0Xf94

#byte portd=0Xf83
#byte trisd= 0Xf95

#byte porte=0Xf84
#byte trise= 0Xf96
*/
#byte intcon2=0xff1

/*#byte t3con=0xfb1
#byte tmr3l=0xfb2
#byte tmr3h=0xfb3

#byte eccpr1l=0xfbb
#byte eccpr1h=0xfbc
#byte eccp1con=0xfba*/

#byte tmr0l=0xfd6
#byte tmr0h=0xfd7
#byte CONFIG1H = 0x300001

//#bit TRIG=portb.1
//#bit key=portb.4

#bit reg=porte.0
#bit rw=porte.1
#bit en=porte.2

#bit KEY1 = portb.4


