  
  #define RS	 (1 <<10)
  #define EN	 (1 <<13) 
  
 void LCD_command(unsigned char comm) ;
 void LCD_data(unsigned char data) ;
 void LCD_display( int ,unsigned int b);
 void LCD_str(unsigned char* str);
 void LCD_init(void) ;

  
  
  //lcd inti
void LCD_init(void) 
{
 LCD_command(0x38);
 delay_ms(2);
 LCD_command(0x06);
  delay_ms(2);
 LCD_command(0x0c);
  delay_ms(2);
 LCD_command(0x01);
  delay_ms(2);
}

 
///command function
void LCD_command(unsigned char comm) 
 {
  int temp;
  temp=(comm<<16);
  IOCLR0=0X00FF0000;
  IOSET0=temp;

  
  IOCLR0=RS;
  //IOCLR1=RW;
  IOSET0=EN;
  delay_ms(2);
  IOCLR0=EN;

}
///data function

void LCD_data(unsigned char data) 
 {
  int temp;
  temp=(data<<16);
  IOCLR0=0X00FF0000;
  IOSET0=temp;
  IOSET0=RS;
 // IOCLR1=RW;
  IOSET0=EN;
  delay_ms(2);
  IOCLR0=EN;

 }



  //lcd  number display

   void LCD_display(int pass, unsigned int b)
   {
     unsigned int x[5],j;
	 for(j=0;j<5;j++)
	 {
	 x[j] =b%10;
	 b=b/10;
	 delay_ms(1);
	 }

	LCD_command(0xc2);
	delay_ms(1);
   
    LCD_data(x[4]|0x30); 
    LCD_data(x[3]|0x30);
	LCD_data(x[2]|0x30);
	LCD_data(x[1]|0x30);
	//LCD_str(".");
	LCD_data(x[0]|0x30);
	delay_ms(2);
  }
 						   

  // lcd character 	display
 void LCD_str(unsigned char* str)
{
  int j;
  for (j=0;j<16 && str[j]!=0;j++)  					
  {
     LCD_data(str[j]);					
  }
 
}