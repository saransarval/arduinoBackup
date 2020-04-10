

#byte trisd=0x88
#byte portd=0x08

#byte trise=0x89
#byte porte=0x09


#bit rs=0x09.0
#bit rw=0x09.1
#bit en=0x09.2



void lcd_inti(void );
void lcd_command(unsigned char );
void lcd_data(unsigned char);
void lcd_clear(void );
void project(void);
void display(int16 ,int1 );


void lcd_clear(void)
{
  lcd_command(0x01);
 }

void lcd_inti(void )
{
	lcd_command(0x01);
	lcd_command(0x02);
	lcd_command(0x06);
	lcd_command(0x0c);
	lcd_command(0x38);

 }

void lcd_command(unsigned char cmd )
	{

     rs=0;
	  rw=0;
     portd=cmd;
     en=1;
     delay_ms(1);
     en=0;
    }

void lcd_data(unsigned char data)
	{

    rs=1;
	 rw=0;
    Portd=data;
    en=1;
    delay_ms(1);
    en=0;
   }



	void project()
    {
      const unsigned char name[]={"     MOTOR SPEED AND DIRECTION MONITERING SYSTEM    "};
      unsigned char dis[16],i=0,j=0,k=0;
				for(i=0;i<60;i++)
				{
					for(j=0,k=i;j<16;j++,k++)
						dis[j]=name[k];
					for(j=0;j<16;j++)
						lcd_data(dis[j]);
					delay_ms(250);
					lcd_command(0x01);
					lcd_command(0x80);
				}
	}


 void display( int16 value,INT1 PASS)
   {
      int a[6],i;
      if(PASS==0)
      {

      lcd_command(0x80);
      lcd_data("voltage:");
      }
		ELSE
		{
      lcd_command(0xc0);
      lcd_data("current:");
      }
      for(i=0;i<6;i++)
      {
         a[i]=value%10;
         value=value/10;
      }
      lcd_data(a[5]|0x30);
      lcd_data(a[4]|0x30);
      lcd_data(a[3]|0x30);
      lcd_data(a[2]|0x30);
      lcd_data(a[1]|0x30);
      lcd_data(a[0]|0x30);
		delay_ms(1);

   }

