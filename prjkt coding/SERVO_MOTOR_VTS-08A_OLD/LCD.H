
#BYTE PORTD=0X08
#BYTE TRISD=0X88
#BYTE TRISE=0X89
#BYTE PORTE=0X09

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2


void command(unsigned char com)
{
 portd=com;
 reg=0;rw=0;
 en=1;delay_ms(1);en=0;
}

void data(unsigned char da)
{
portd=da;
reg=1;rw=0;
en=1;delay_ms(1);en=0;
}

void lcd_int(void)
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

