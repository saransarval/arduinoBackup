#byte    trisa    = 0xf92
#byte    trisb    = 0xf93
#byte    trisc    = 0xf94
#byte    trisd    = 0xf95
#byte    trise    = 0xf96
#byte    trisf    = 0xf97
#byte    trisg    = 0xf98
#byte    trish    = 0xf99
#byte    trisj    = 0xf9a

#byte    TXSTA   = 0xFAC
#byte    RCSTA   = 0xFAB
#byte    RXREG   = 0xFAE 
#byte    porta   = 0xF80
#byte    portb   = 0xF81
#byte    portc   = 0xF82
#byte    portd   = 0xF83
#byte    porte   = 0xF84
#byte    portf   = 0xF85  
#byte    portg   = 0xF86  
#byte    porth   = 0xF87  
#byte    portj   = 0xF88  

#byte    LATA    = 0xF89  
#byte    LATB    = 0xF8A
#byte    LATC    = 0xF8B
#byte    LATD    = 0xF8C
#byte    LATE    = 0xF8D
#byte    LATF    = 0xF8E
#byte    LATG    = 0xF8F
#byte    LATH    = 0xF90
#byte    LATJ    = 0xF91

#byte   Adcon1   = 0xfc1
#byte   CMCON   = 0xfB4
#byte   RCON	 = 0xfd0
#byte   STKPTR   = 0xffc
#byte  PIR1      = 0xf9e
#byte  PIR3      = 0xfa4
#byte  T3CON     = 0xfb1
#byte  pr2       = 0xfcb
#byte  HLVDCON   = 0xfd2
#byte  PIE2      = 0xfa0
#byte  T1CON     = 0xFCD
#byte  tmr1h     = 0xfcf
#byte  tmr1l     = 0xfce
#bit   HLVDIE    = PIE2.2
#bit   RCIF      = PIR1.5   
//SINGLE BIT DECLARATION

//PORTA BITS
#bit    RA0		= PORTA.0
#bit    RA1		= PORTA.1
#bit    RA2		= PORTA.2
#bit    RA3		= PORTA.3
#bit    RA4		= PORTA.4
#bit    RA5		= PORTA.5

//PORTB BITS
#bit    RB0		= PORTB.0
#bit    RB1		= PORTB.1
#bit    RB2		= PORTB.2
#bit    RB3		= PORTB.3
#bit    RB4		= PORTB.4
#bit    RB5		= PORTB.5
#bit    RB6		= PORTB.6
#bit    RB7		= PORTB.7

//PORTC BITS
#bit    RC0		= PORTC.0
#bit    RC1		= PORTC.1
#bit    RC2		= PORTC.2
#bit    RC3		= PORTC.3
#bit    RC4		= PORTC.4
#bit    RC5		= PORTC.5
#bit    RC6		= PORTC.6
#bit    RC7		= PORTC.7

//PORTD BITS
#bit    RD0		= PORTD.0
#bit    RD1		= PORTD.1
#bit    RD2		= PORTD.2
#bit    RD3		= PORTD.3
#bit    RD4		= PORTD.4
#bit    RD5		= PORTD.5
#bit    RD6		= PORTD.6
#bit    RD7		= PORTD.7

//PORTE BITS
#bit    RE0		= PORTE.0
#bit    RE1		= PORTE.1
#bit    RE2		= PORTE.2
