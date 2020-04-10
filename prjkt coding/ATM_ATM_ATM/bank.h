
uchar pp=0,pass=0,enter_pass=0,Q=0;
//char msg_read[12];
uchar flag=0;

uchar fata=0,pass_curt=0,temp=0,PERSON=0;
uchar i,card=0;
uchar bk[3]={0,0,0};
uchar pr1=0,pr2=0;
uchar po1=0,po2=0,t=0;
uchar MODE=0;
uchar option_set=0,option_m=0,check_yes=0;

uchar bank2=0,baku2=0;

uchar wrong=0,high_low=0;
uint total_amu[6]={50000,30000,10000,60000,40000,20000},b1=0,b2=0;
 
void draw(void);
void mode_sec(void);
void disp_name(void); 
void bank(void); 
void bank_amout(void); 
void cash_trasfer(void);
void bank_2(void);
void mode_new_sec();



   void disp_name()
   {

    if(msg_read[10]=='8'&&msg_read[11]=='D')
	{

	LCD_command(0x01);
	LCD_command(0x80);
	LCD_str(" NAME:NAME1  ");
	LCD_command(0xC0);
	LCD_str(" CARD NO:0001   ");
	LCD_command(0x90);
	LCD_str(" VALIDITY:    ");
	LCD_command(0xD0);
	LCD_str(".....22.05.2024");
      //pr1=1;po1=1;fata=1;
	  putstr("C1");
	//putchar('C');putchar('1');
	    pr1=1;PERSON=1;wrong=0;
	bk[0]=0;bk[1]=0;bk[2]=0;
	 }


   if(msg_read[10]=='2'&&msg_read[11]=='B')
	{
   	LCD_command(0x01);
	LCD_command(0x80);
	LCD_str(" NAME:NAME2  ");
	LCD_command(0xc0);
	LCD_str(" CARD NO:0012   ");
	LCD_command(0x90);
	LCD_str(" VALIDITY:    ");
	LCD_command(0xD0);
	LCD_str(".....06.03.2016");

	  // pr2=1;po2=1;fata=2;
	  putstr("C2");
	//putchar('C');putchar('2');
	  pr2=1;PERSON=2;wrong=0;
	   bk[0]=0;bk[1]=0;bk[2]=0;
	}
    
      i=0;
  delay_ms(3000);

}



void mode_new_sec()
{

  LCD_command(0x01);
  
      while(1)
     {
	
//	LCD_command(0x80);
//	LCD_str(" MODE ....");
	LCD_command(0x80);
	LCD_str("1GENARAL MODE");
	LCD_command(0xc0);
	LCD_str("2PETROL BUNK");

	LCD_command(0x90);
	LCD_str("OPTION IS: ");
      pp=keypad(0);
	if(pp==1)
	  {
		MODE=11;putchar('G');
		bk[0]=0;bk[1]=0;bk[2]=0;
	    delay_ms(300);
	    break;
	  }
	if(pp==2)
	  {
	    MODE=22; putchar('P');//putchar('1');
		bk[0]=0;bk[1]=0;bk[2]=0;
		delay_ms(300);
		break;
		   
	 }



   }

}





void mode_sec()
   {
     LCD_command(0x01);card=1;

	  if(pr1==1)
	    { po1=1;delay_ms(2);}
	  if(pr2==1)
	    { po2=1;delay_ms(2);}

     while(1)
     {
	
//	LCD_command(0x80);
//	LCD_str(" MODE ....");
	LCD_command(0x80);
	LCD_str("1ACCOUNT DETAIL");
	LCD_command(0xc0);
	LCD_str("2CASH WITHDRAWAL");
	LCD_command(0x90);
	LCD_str("3CASH TRANSFER");

	LCD_command(0xd0);
	LCD_str("OPTION IS: ");
      pp=keypad(0);
	//delay_ms(250);
      	if(pp==1)
	        {
		    MODE=2;bk[0]=0;bk[1]=0;bk[2]=0;
	          delay_ms(300);
	          break;
		  }
	     if(pp==2)
	       {
		  MODE=4; putchar('W');//putchar('1');
		bk[0]=0;bk[1]=0;bk[2]=0;
		  delay_ms(300);
		   break;
		   
		 }

		if(pp==3)
	       {
		  MODE=6; putchar('T');//putchar('1');
		  bk[0]=0;bk[1]=0;bk[2]=0;
		  delay_ms(300);
		  break;
		   
		 }
      }

    }




void bank(void)
{

 ///////////////////////////bank1.............
    if(bk[0]==1)
    {

      LCD_command(0x01);
	  LCD_command(0x80);

	  LCD_str(" SBI BANK  ");
      delay_ms(5);

	if(pr1==1)
	{

      LCD_command(0xc0);
	LCD_str("  NAME:NAME1  ");
	LCD_command(0x90);
	LCD_str("  ACC NO:0011   ");
	LCD_command(0xd0);
	LCD_str("  BRANCH:AAA22  ");
//	pr1=0;pr2=0;
    i=0;
	 }


	if(pr2==1)
	{
      LCD_command(0xc0);
	LCD_str("  NAME:NAME2  ");
	LCD_command(0x90);
	LCD_str("  ACC NO:0021   ");
	LCD_command(0xd0);
	LCD_str("  BRANCH:BBB22   ");
//	pr1=0;pr2=0;
     i=0;
	 }



	// bk[0]=0;
    //bk=0; pr1=0;pr2=0;
	i=0;
    }

  ///////////////////////////bank2.............

    if(bk[1]==2)
    {

      LCD_command(0x01);
	  LCD_command(0x80);

	  LCD_str("  AXIS BANK  ");
      delay_ms(5);

	if(pr1==1)
	{
      LCD_command(0xc0);
	LCD_str("  NAME:NAME1  ");
	LCD_command(0x90);
	LCD_str("  ACC NO:0012   ");
	LCD_command(0xd0);
	LCD_str("  BRANCH:AAA22  ");
	//pr1=0;pr2=0;
	i=0;
	 }


	if(pr2==1)
	{
      LCD_command(0xc0);
	LCD_str("  NAME:NAME2  ");
	LCD_command(0x90);
	LCD_str("  ACC NO:0022   ");
	LCD_command(0xd0);
	LCD_str("  BRANCH:BBB62   ");
	//pr1=0;pr2=0;
	i=0;
	 }

    //pr1=0;pr2=0;
	i=0;
	 //bk[1]=0;
    }


    ///////////////////////////bank3.............
     if(bk[2]==3)
    {
      LCD_command(0x01);
	if(pr2==1)
	{
	LCD_command(0x80);
	LCD_str("ICICI BANK  ");
      delay_ms(5);
	}
	if(pr1==1)
	{
	LCD_command(0x80);
	LCD_str("PNB BANK  ");
      delay_ms(5);
	}

	if(pr1==1)
	{
      LCD_command(0xc0);
	LCD_str("  NAME:NAME1  ");
	LCD_command(0x90);
	LCD_str("  ACC NO:0013   ");
	LCD_command(0xd0);
	LCD_str("  BRANCH:AAA66 ");
	//pr1=0;pr2=0;
	i=0;
	 }


	if(pr2==1)
	{
      LCD_command(0xc0);
	LCD_str("  NAME:NAME2  ");
	LCD_command(0x90);
	LCD_str("  ACC NO:0023   ");
	LCD_command(0xd0);
	LCD_str("  BRANCH:BBB55  ");
	//pr1=0;pr2=0;
	i=0;
	 }

            //pr1=0;pr2=0;
			i=0;
			//bk=0;
    }
     bk[2]=0;
     delay_ms(3000);
 }


    void bank_amout()
{

       unsigned char j=0,x[5];
	
	if(Q==1){Q=0;if(total_amu[0]>=b1){total_amu[0]=total_amu[0]-b1;}else high_low=1;b2=total_amu[0];}
	if(Q==2){Q=0;if(total_amu[1]>=b1){total_amu[1]=total_amu[1]-b1;}else high_low=1;b2=total_amu[1];}
	if(Q==3){Q=0;if(total_amu[2]>=b1){total_amu[2]=total_amu[2]-b1;}else high_low=1;b2=total_amu[2];}
	if(Q==4){Q=0;if(total_amu[3]>=b1){total_amu[3]=total_amu[3]-b1;}else high_low=1;b2=total_amu[3];}
	if(Q==5){Q=0;if(total_amu[4]>=b1){total_amu[4]=total_amu[4]-b1;}else high_low=1;b2=total_amu[4];}
	if(Q==6){Q=0;if(total_amu[5]>=b1){total_amu[5]=total_amu[5]-b1;}else high_low=1;b2=total_amu[5];}
  

   if(high_low!=1)
   {
    if(MODE!=2)
      num(b1);
	 // putstr(b1);
      high_low=0;
	 for(j=0;j<5;j++)
	 {
	 x[j] =b2%10;
	 b2=b2/10;
	 delay_ms(1);
	 }
	 delay_ms(1000);
	 LCD_command(0x01);
	 LCD_command(0x80);
	 delay_ms(1);
     LCD_str("TOTAL AMOUNT ");
     LCD_command(0xc0);
	 LCD_str("......");
	 delay_ms(1);
	  b1=0;b2=0;
	LCD_data(x[4]|0x30);
    LCD_data(x[3]|0x30);
	LCD_data(x[2]|0x30);
	LCD_data(x[1]|0x30);
	LCD_data(x[0]|0x30);
	delay_ms(200);
	}

		else 
	{
	     high_low=0;
	 	 LCD_command(0x01);
	     LCD_command(0xc0);
	     delay_ms(1);
         LCD_str("LOW BALANCE ");	delay_ms(2000);
         //LCD_command(0xc0);

	}
	
  
	b1=0;b2=0; Q=0;

}

void draw()
{
unsigned char keyp2[6]={0};
b1=0;
while(1)
{
  pp=keypad(0);
  delay_ms(200);
  if(pp=='#')
  {
   keyp2[5]=keyp[0];keyp2[4]=keyp[1];keyp2[3]=keyp[2];keyp2[2]=keyp[3];keyp2[1]=keyp[4];
   if(key1==6)
  {
   b1=keyp2[5]*10000+keyp2[4]*1000+keyp2[3]*100+keyp2[2]*10+keyp2[1]*1; 
   keyp2[1]=0;
  }

  if(key1==5)
  {
  b1=keyp2[5]*1000+keyp2[4]*100+keyp2[3]*10+keyp2[2]*1;
   keyp2[1]=keyp2[0]=0;
  }

    if(key1==4)
  {
    b1=keyp2[5]*100+keyp2[4]*10+keyp2[3]*1;
    keyp2[2]=keyp2[1]=keyp2[0]=0;
  }

   if(key1==3)
  {
    b1=keyp2[5]*10+keyp2[4]*1;
    keyp2[3]=keyp2[2]=keyp2[1]=keyp2[0]=0;
  }

   if(key1==2)
  {
    b1=keyp2[5]*1;
    keyp2[4]=keyp2[3]=keyp2[2]=keyp2[1]=keyp2[0]=0;
  }
  

   
    delay_ms(400);
    keyp[5]=keyp[4]=keyp[3]=keyp[2]=keyp[1]=keyp[0]=0;
    keyp2[5]=keyp2[4]=keyp2[3]=keyp2[2]=keyp2[1]=keyp2[0]=0;
    delay_ms(400);
    break;
  }

 }

}



void bank_2(void)
{

 	delay_ms(10);
	if(pr1==1)
	{
	 	LCD_command(0x01);
		LCD_command(0x80);
		LCD_str("SELET BANK ");
		LCD_command(0xc0);
	    delay_ms(10);
	   if(bk[0]==0 && bk[1]==0)
	     {
		  LCD_str(" 1 : SBI BANK   ");LCD_command(0x90);LCD_str(" 2 : AXIS BANK   "); bank2=12;  }
	   if(bk[0]==0 && bk[2]==0)
	     {
		  LCD_str(" 1 : SBI BANK   "); LCD_command(0x90);LCD_str(" 2 : PNB BANK    "); bank2=13;  }

	    if(bk[1]==0 && bk[2]==0)
	     {
		   LCD_str(" 1: AXIS BANK   "); LCD_command(0x90);LCD_str(" 2 : PNB BANK    "); bank2=14;  }                      
	 }

		  
	if(pr2==1)
	{

    	LCD_command(0x01);
		LCD_command(0x80);
		LCD_str("SELET BANK ");
		LCD_command(0x90);
	   delay_ms(10);
	   if(bk[0]==0 && bk[1]==0)
	     {
		  LCD_str(" 1 : SBI BANK   ");LCD_command(0x90);LCD_str(" 2 : AXIS BANK   ");  bank2=22; }
	   if(bk[0]==0 && bk[2]==0)
	     {
		  LCD_str(" 1 : SBI BANK   "); LCD_command(0x90);LCD_str(" 2 : ICICI BANK   "); bank2=23;}

	    if(bk[1]==0 && bk[2]==0)
	     {
		  LCD_str(" 1 : AXIS BANK   "); LCD_command(0x90);LCD_str(" 2 : ICICI BANK   "); bank2=24;}

	 }

	  LCD_command(0xD0);
	  LCD_str("OPTION IS: ");baku2=1;
	 
	  while(baku2)
	  {
	  	  pp=keypad(0);delay_ms(100);
		if((bank2==12 ||bank2==13) && pp==1)
		{
		   LCD_command(0x01);LCD_command(0xd0);
		  LCD_str(" SBI BANK   ");bank2=1; baku2=0;	  putstr("B1");
		   delay_ms(20);	
		}


	   if((bank2==22 ||bank2==23) && pp==1)
		{
		   LCD_command(0x01);LCD_command(0xd0);
		  LCD_str(" SBI BANK   ");bank2=4;	baku2=0;  putstr("B1");    
		   delay_ms(20);	
		}


	   if((bank2==13 ||bank2==14) && pp==2)
		{
		    LCD_command(0x01);LCD_command(0xd0);
		  LCD_str("  PNB BANK  "); bank2=7; baku2=0;   putstr("B3");		  
		   delay_ms(20);	
		}

		
	   if((bank2==23 ||bank2==24) && pp==2)
		{
		    LCD_command(0x01);LCD_command(0xd0);
		  LCD_str("  ICICI BANK   ");bank2=6; baku2=0;	putstr("B3");
		   delay_ms(20);	
		}

	   if(bank2==12 && pp==2)
		{
		    LCD_command(0x01);LCD_command(0xd0);
		  LCD_str("  AXIS BANK   ");bank2=2; baku2=0;	putstr("B2");	  
		   delay_ms(20);	
		}


	  if(bank2==22&& pp==2)
		{
		    LCD_command(0x01);LCD_command(0xd0);
		  LCD_str("  AXIS BANK   ");bank2=5; baku2=0;	putstr("B2");	  
		   delay_ms(20);	
		}

	   if(bank2==14 && pp==1)
		{
		   LCD_command(0x01);LCD_command(0xd0);
		  LCD_str("  AXIS BANK   ");bank2=2; baku2=0;	putstr("B2");	 
		   delay_ms(20);	
		}

	   if(bank2==24 && pp==1)
		{
		   LCD_command(0x01);LCD_command(0xd0);
		  LCD_str(" AXIS BANK   ");bank2=5; baku2=0;	putstr("B2");
		  delay_ms(20);		  

		}

	    
	  b1=0;
   }

    //delay_ms(2000);

bk[0]=bk[1]=bk[2]=0;


   }







void cash_trasfer(void)
{

    unsigned char j=0,x[5];

	if(Q==1){if(total_amu[0]>=b1){total_amu[0]=total_amu[0]-b1;}else high_low=1;b2=total_amu[0];}
	if(Q==2){if(total_amu[1]>=b1){total_amu[1]=total_amu[1]-b1;}else high_low=1;b2=total_amu[1];}
	if(Q==3){if(total_amu[2]>=b1){total_amu[2]=total_amu[2]-b1;}else high_low=1;b2=total_amu[2];}
	if(Q==4){if(total_amu[3]>=b1){total_amu[3]=total_amu[3]-b1;}else high_low=1;b2=total_amu[3];}
	if(Q==5){if(total_amu[4]>=b1){total_amu[4]=total_amu[4]-b1;}else high_low=1;b2=total_amu[4];}
	if(Q==6){if(total_amu[5]>=b1){total_amu[5]=total_amu[5]-b1;}else high_low=1;b2=total_amu[5];}
  


   
////////////////////////////////////// person1 bank...............................	

if(high_low!=1)
{
    high_low=0;


	//////////////////////...........................bank fine new valuwe........

 

	num(b1);

	 for(j=0;j<5;j++)
	 {
	 x[j] =b2%10;
	 b2=b2/10;
	 delay_ms(1);
	 }
	 delay_ms(1000);
	 LCD_command(0x01);
	 LCD_command(0x80);
	 delay_ms(1);
	 if(Q==1||Q==4)LCD_str("SBI BANK ...    ");
	 if(Q==2||Q==5)LCD_str("AXIS BANK ...   ");
	 if(Q==3)LCD_str("  PNB BANK....      ");
	 if(Q==6)LCD_str("  ICICI BANK.......   ");
     LCD_command(0xc0);
	 LCD_str("AMOUNT...");
	 delay_ms(1);
	 
	LCD_data(x[4]|0x30);
    LCD_data(x[3]|0x30);
	LCD_data(x[2]|0x30);
	LCD_data(x[1]|0x30);
	LCD_data(x[0]|0x30);
	delay_ms(2000);	b2=0;







	if(Q==1){if(bank2==2){Q=0;total_amu[1]=total_amu[1]+b1;b2=total_amu[1];}}
	if(Q==1){if(bank2==7){Q=0;total_amu[2]=total_amu[2]+b1;b2=total_amu[2];}}

	if(Q==2){if(bank2==1){Q=0;total_amu[0]=total_amu[0]+b1;b2=total_amu[0];}}
	if(Q==2){if(bank2==7){Q=0;total_amu[2]=total_amu[2]+b1;b2=total_amu[2];}}

	if(Q==3){if(bank2==1){Q=0;total_amu[0]=total_amu[0]+b1;b2=total_amu[0];}}
	if(Q==3){if(bank2==2){Q=0;total_amu[1]=total_amu[1]+b1;b2=total_amu[1];}}

////////////////////////////////////// person2 bank...............................	
	if(Q==4){if(bank2==5){Q=0;total_amu[4]=total_amu[4]+b1;b2=total_amu[4];}}
	if(Q==4){if(bank2==6){Q=0;total_amu[5]=total_amu[5]+b1;b2=total_amu[5];}}

	if(Q==5){if(bank2==4){Q=0;total_amu[3]=total_amu[3]+b1;b2=total_amu[3];}}
	if(Q==5){if(bank2==6){Q=0;total_amu[5]=total_amu[5]+b1;b2=total_amu[5];}}

	if(Q==6){if(bank2==4){Q=0;total_amu[3]=total_amu[3]+b1;b2=total_amu[3];}}
	if(Q==6){if(bank2==5){Q=0;total_amu[4]=total_amu[4]+b1;b2=total_amu[4];}}



	 bank2=0; Q=0;
	}


	else 
	{
	      high_low=0;
	 	 LCD_command(0x01);
	     LCD_command(0xc0);
	     delay_ms(1);
         LCD_str("LOW BALANCE ");	delay_ms(2000);
         //LCD_command(0xc0);

	}
	

  
	b1=0;b2=0; Q=0;
	 

}


void petrol()
{
 if(PERSON==1)
 {
  	LCD_command(0x01);
	LCD_command(0x80);
	LCD_str(" * : SBI BANK   ");fata=11;
	putstr("B1");
 }

  if(PERSON==2)
 {
   	LCD_command(0x01);
	LCD_command(0x80);
	LCD_str(" * : ICICI BANK   ");fata=23;
	putstr("B3");
 }

	LCD_command(0xC0);
	LCD_str(" ENTER........");
	LCD_command(0x90);
	LCD_str(" THE PASSWORD ");
 	keyp[3]=keyp[2]=keyp[1]=keyp[0]=0,key1=0;
	LCD_command(0xD0);
	//LCD_command(0xD0);
	 LCD_str("   ");
	passward();




}