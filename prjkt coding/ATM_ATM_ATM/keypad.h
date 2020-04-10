#define R1 (1<<16)
#define R2 (1<<17)
#define R3 (1<<18)
#define R4 (1<<19)

#define C1 (1<<20)
#define C2 (1<<21)
#define C3 (1<<22)							      
#define C4 (1<<23)

#define PIN IOPIN1

unsigned char PATA=0;
unsigned char keyp[6]={0},key1=0,check=0;

unsigned char keypad(unsigned char);
unsigned char keypad(unsigned char nom)
               {

                 
			PATA=0;
     
			 PIN=R2|R3|R4; 
			  if(( PIN &(C1|C2|C3|C4) )!= (C1|C2|C3|C4))
              {
			   	
                       switch(PIN&0x00F00000)
                       {
					   case 0x00700000 : LCD_str("A");PATA='A';putchar('A');delay_ms(5);break;
                       case 0x00B00000 : LCD_str("3");PATA= 3;delay_ms(5);break;
                       case 0x00D00000 : LCD_str("2");PATA= 2;delay_ms(5);break;
                       case 0x00E00000 : LCD_str("1");PATA= 1;delay_ms(5);break;
                      }
			  if(PATA!='A')
			  {
			   keyp[key1]=PATA;key1++; }
              }
		  
			  	 
			  PIN=R1|R3|R4; 
			 if(( PIN &(C1|C2|C3|C4) )!= (C1|C2|C3|C4))
              {
			   	
                       switch(PIN&0x00F00000)
                       {

					   //case 0x00700000 : LCD_str("B");PATA= B;delay_ms(5);break;
                       case 0x00B00000 : LCD_str("6");PATA=6;delay_ms(5);break;
                       case 0x00D00000 : LCD_str("5");PATA=5;delay_ms(5);break;
                       case 0x00E00000 : LCD_str("4");PATA=4;delay_ms(5);break;
						
                       }
			   keyp[key1]=PATA; key1++;  
              }
              	  

			  PIN=R1|R2|R4; 
			 if(( PIN &(C1|C2|C3|C4) )!= (C1|C2|C3|C4))
              {
			   		
                       switch(PIN&0x00F00000)
                       {
					   case 0x00700000 : LCD_str("C");PATA='C';delay_ms(5);break;
                       case 0x00B00000 : LCD_str("9");PATA=9;delay_ms(5);break;
                       case 0x00D00000 : LCD_str("8");PATA=8;delay_ms(5);break;
                       case 0x00E00000 : LCD_str("7");PATA=7;delay_ms(5);break;
                       }
			   if(PATA!='C')
			   {
			  keyp[key1]=PATA;  key1++; 
			      }   
             } 
			 									      

			 PIN=R1|R2|R3; 
		    if(( PIN &(C1|C2|C3|C4) )!= (C1|C2|C3|C4))
              {
			   	
                       switch(PIN&0x00F00000)
                       {
					   case 0x00700000 : LCD_str("D");PATA='D';putchar('D');delay_ms(5);break;
                       //case 0x00B00000 : LCD_str("=");PATA=1;delay_ms(5);break;
                       case 0x00D00000 : LCD_str("0");PATA=0;delay_ms(5);break;
                       case 0x00E00000 : LCD_str(" ");PATA='#';delay_ms(5);break;
                       }
			   if(PATA!='D')
			   {
			  keyp[key1]=PATA;  key1++; 
			      }
              }
		 //DATA=(DATA&0x00FF0000);
		 //DATA=DATA>>16; 

	  if(PATA=='C')
	  {
	 	 LCD_command(0x01);
	     LCD_command(0xC0);
	     LCD_str(" ENTER........");
	     LCD_command(0x90);
	     LCD_str(" THE PASSWORD ");
	     LCD_command(0xD0);

	  	key1=0;delay_ms(50);
	  }	
	  
	  if(key1==4 && nom==1)
	  {
	     check=1; 
	     delay_ms(50);
	  }
	  delay_ms(50);
	  return PATA;
	  	  	 
       
        }

	             