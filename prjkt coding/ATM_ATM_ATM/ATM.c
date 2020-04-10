#include <LPC214X.H>

#define uint   unsigned int
#define uchar  unsigned char 

uchar msg_read[12]={0},msg_read1[12]={0},flag_u0=0,flag_u1=0; 
void passward(void);
#include"delay.h"
#include"pll.h"
#include"lcd.h"
#include"uart0.h"
#include"keypad.h"
#include"bank.h"
#include"uart0_1.h"

#define RELAY1 (1<<31)


void main()
{

 PINSEL0=0X00000000;
 PINSEL1=0x00000000;
 PINSEL2=0x00000000;
 IOPIN0= 0X00000000;
 IODIR0= 0X00000000;
 IOPIN1= 0X00000000;

 IO1DIR = R1 | R2 | R3 | R4 |RELAY1;
 IODIR0  = 0X00FF0000|RS|EN;

  lpc2148_pll();

  LCD_init();
  delay_ms(20);
  Init_UART0();
  Init_UART1();
  Init_VIC();

  LCD_init();
  delay_ms(20);

  LCD_command(0x80);
  LCD_str("UNIVERSAL ATM ");
  LCD_command(0x90);
  LCD_str("CARD ...");
  delay_ms(4000);
  LCD_command(0x01);
  delay_ms(1);

   while(1)
   {



	 if(flag_u1==1)
	  {
	  flag_u1=0;
	  disp_name();
	  mode_new_sec();
	  if(MODE==11)
	  mode_sec();
	  else if(MODE==22)
	    {
		 petrol();
	    }
	   }


	while(card==1)
	{
	 

	  pp=keypad(0);
	 
	 // delay_ms(10);
        if(po1==1)
	   {
		LCD_command(0x01);
		LCD_command(0x80);

	     {
		  LCD_str(" 1 : SBI BANK   ");
		  LCD_command(0xc0);
		  LCD_str(" 2 : AXIS BANK   ");
		  LCD_command(0x90);
		  LCD_str(" 3 : PNB BANK    ");
		}
		i=0;
	
		 po1=0;po2=0;i=0;
		 bk[0]=0;bk[1]=0;bk[2]=0;
	 }


        if(po2==1)
	  {
		LCD_command(0x01);
		LCD_command(0x80);

	     {
          LCD_str(" 1 : SBI BANK   ");
		  LCD_command(0xc0);
		  LCD_str(" 2 : AXIS BANK   ");
		  LCD_command(0x90);
		  LCD_str(" 3 : ICICI BANK   ");
		}
		i=0;
			po1=0;po2=0;i=0;
			bk[0]=0;bk[1]=0;bk[2]=0;
	 }

	LCD_command(0xd0);
	LCD_str("OPTION IS: ");
	delay_ms(200);

	if((pp==1))
	 {
	 card=0;
     bk[0]=1;
	 delay_ms(20);
	 enter_pass=1;
	 if(PERSON==1)fata=11;
	 if(PERSON==2)fata=21;
	 if(MODE!=2)
	 putstr("B1");
	 //putchar('B');putchar('1');
	 //bank();
	 delay_ms(20);bk[1]=0;bk[2]=0;

	 }


	if((pp==2))
	 {
	 card=0;
       bk[1]=2;
	 delay_ms(20);
	 enter_pass=1;
	 if(PERSON==1)fata=12;
	 if(PERSON==2)fata=22;
	 if(MODE!=2)
	 putstr("B2");
	 //putchar('B');putchar('2');
	 //bank();
	 delay_ms(20);bk[0]=0;bk[2]=0;
	 }


      if((pp==3))
	 {
	 card=0;
       bk[2]=3;
	 if(PERSON==1)fata=13;
	 if(PERSON==2)fata=23;
	 delay_ms(20);
	 if(MODE!=2)
	 putstr("B3");
	 //putchar('B');putchar('3');
	 enter_pass=1; bk[0]=0;bk[1]=0;
	 delay_ms(20);
	 }


	 if(enter_pass==1)
	 {
	  enter_pass=2; //pp=0;
	 LCD_command(0x01);
	 LCD_command(0xC0);
	 LCD_str(" ENTER........");
	 LCD_command(0x90);
	 LCD_str(" THE PASSWORD ");
	 LCD_command(0xD0);
	 LCD_str("              ");
	 pp=0;
	 }
	  					     
	}

	    if( enter_pass==2)
	    {
	      enter_pass=0;
	      keyp[3]=keyp[2]=keyp[1]=keyp[0]=0,key1=0;
	      LCD_command(0xD0);
	      passward();
	    }




		 if(option_set==1)
		 {
		   
		   	LCD_command(0x90);
     	    LCD_str(" GO BACK TO HOME...?");

	        LCD_command(0xd0);
	        LCD_str("OPTION IS: ");


		   option_set=0;option_m=1;
		   while(option_m)
		   {
		   check_yes=keypad(0);
			if(check_yes=='A')
			{
			     LCD_command(0xD0);
				 LCD_str("yes...."); check_yes=0;  LCD_command(0x01); option_m=0;
				 //mode_sec();
				 mode_new_sec();

				 	  if(MODE==11)
	                       mode_sec();
	                   else if(MODE==22)
	                         {
		                       petrol();
	                          }

		    }

				if(check_yes=='D')
			{
			     LCD_command(0x01);putchar('D');
			     LCD_command(0xD0);
				 LCD_str("THANK  U....."); check_yes=0; option_m=0;
				 break;

		    }

		 }
	  }
	

	  }

	}



void passward(void)
{
  uint pep=0;
   while(1)
	{
	  keypad(1);
	  delay_ms(180);
	 if(  check==1)
	 {
	   	 check=0;
	   ///bk1p1

	   if(fata==11)
	   {if(keyp[3]==1 && keyp[2]==1 && keyp[1]== 0 && keyp[0]==1 ){pass_curt=1;Q=1;}}

	   ///bk2p1

	   if(fata==12)
	   {if(keyp[3]==2 && keyp[2]==2 && keyp[1]== 0 && keyp[0]==1 ){pass_curt=1;Q=2;}}

	   ///bk3p1

	   if(fata==13)
	   {if(keyp[3]==3 && keyp[2]==3 && keyp[1]== 0 && keyp[0]==1 ){pass_curt=1;Q=3;}}

	   ///bk1p2
	   if(fata==21)
	   {if(keyp[3]==4 && keyp[2]==4 && keyp[1]== 0 && keyp[0]==2 ){pass_curt=1;Q=4;}}

	   ///bk2p2
	   if(fata==22)
	   {if(keyp[3]==8 && keyp[2]==3 && keyp[1]== 0 && keyp[0]==2 ){pass_curt=1;Q=5;}}

	   ///bk3p2
	   if(fata==23)
	   {if(keyp[3]==9 && keyp[2]==8 && keyp[1]== 0 && keyp[0]==2 ){pass_curt=1;Q=6;}}




	   if(pass_curt==1)
	   {
	      keyp[3]=keyp[2]=keyp[1]=keyp[0]=0,key1=0;key1=0;
	      LCD_command(0x01);
	      LCD_command(0xC0);
	      LCD_str(" ENTER........");
	      LCD_command(0x90);
	      LCD_str("CORRECT PASSWORD ");
		  pass_curt=0;
		  check=0;



////////////////////////////////////////////////////////////////////////
		  if(MODE==22)
		    {
	         LCD_command(0xc0);MODE=0;
		     LCD_str("AMOUNT..:  ");
             draw();  LCD_command(0xd0);
			 LCD_str("petrol.....");
			 LCD_command(0x90);
			 //num(b1); 
			 IOSET1= RELAY1;
			 for(pep=0;pep<b1;pep++)
			 {
			  LCD_display(0,pep);
			  delay_ms(100);
			 }
			 IOCLR1= RELAY1;
			 bank_amout(); putchar('D');
			 option_set=0;delay_ms(1000);  
			 LCD_command(0xD0);
			 LCD_str("THANK  U.....");
			 pass_curt=0;check_yes='D';break;
		    }

  //////////////////////////////////////////////ACCOUNT DETAIL///////////
		  if(MODE==2)
		    {
	         bank();delay_ms(2000);bank_amout();MODE=0; delay_ms(4);//LCD_command(0x01);
			  putchar('A');
			 option_set=1; pass_curt=0;break;
		    }


 ////////////////////////////////////////////////CASH WITHDRAWAL
		 if(MODE==4)
	    	{
		     LCD_command(0xC0);MODE=0;
		     LCD_str("AMOUNT... ");
	         draw();
		     bank_amout(); //break;

			 delay_ms(4);//LCD_command(0x01);
			 option_set=1; pass_curt=0;break;
		    }

///////////////////////////////////////CASH TRANSFER///////////

		   	 if(MODE==6)
	    	{
		    // LCD_command(0x80);
			 MODE=0;
		     //LCD_str("SELET BANK1 ");
			 delay_ms(20);
			 bank_2();	 
			 //keyp[6]={0};
			 key1=0;check=0;
			 //LCD_command(0x01);
			 LCD_command(0xC0);MODE=0;
		     LCD_str("AMOUNT..:  ");

			 draw();
			 cash_trasfer();
	         
			 //cash_trasfer();
		    // bank_amout(); //break;

			 delay_ms(4);//LCD_command(0x01);
			 //delay_ms(4);//LCD_command(0x01);
			 option_set=1; pass_curt=0;break;
		    }

////////////////////////////////////////////////////////////////

	   }
	   else
	    {
		  LCD_command(0x01);
	      LCD_command(0xC0);
	      LCD_str("INCORRECT....");putstr("00000");delay_ms(2000);	 wrong++;
		  //pass_curt=1;  
		  if(wrong==2)
		  {
		  putchar('D');
		  check=0;option_set=0;pass_curt=0;card=0; break; }
		    
		  option_set=1; pass_curt=0;break;
		   
	    }
	 
	  }
	}
}

