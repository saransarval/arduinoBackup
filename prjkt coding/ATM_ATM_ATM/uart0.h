
 int putchar(int ch);
 int getchar(void);
 void num( unsigned int );
void putstr(const unsigned char *str);

int putchar(int ch)
{
 
if (ch == '\n')
{
while (!(U0LSR & 0x20));
U0THR = 0x0D; 
} 	 
 

while (!(U0LSR & 0x20));
U0THR = ch;
return 0 ; 
}

int getchar (void) 
{
while (!(U0LSR & 0x01));
return(U0RBR);
}


  void num( unsigned int b)
   {
     unsigned int x[5],j;
	 for(j=0;j<5;j++)
	 {
	 x[j] =b%10;
	 b=b/10;
	 delay_ms(1);
	 }			               

	while(j!=0)
    {
	 j--;
       putchar(x[j]+0x30);
	 //if(j==1)
	 //putchar('.');
     }
  }

 
void putstr(const unsigned char *str)
{
   while(1)
   {
      if( *str == '\0' ) break;
      putchar(*str++);
   }
}




 