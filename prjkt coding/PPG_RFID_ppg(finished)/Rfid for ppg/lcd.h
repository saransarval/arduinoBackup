#use delay(clock=11059200)
#byte trisd=0x88
#byte portd=0x08
#byte trise=0x89
#byte porte=0x09

#bit reg=0x09.0
#bit rw=0x09.1
#bit en=0x09.2

void command(unsigned char com)
{
portd=com;
reg=0;
rw=0;
en=1;
delay_ms(2);
en=0;
}

void data(unsigned char da)
{
portd=da;
reg=1;
rw=0;
en=1;
delay_ms(2);
en=0;
}

void lcd_init()
{
command(0x38);
command(0x06);
command(0x0c);
command(0x01);
delay_ms(20);
}
