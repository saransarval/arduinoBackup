 


#define RDA  0x04
								    
void UART0ISR(void)__irq;
void UART1ISR(void)__irq;

uchar rxdat=0,k1=0,k2=0;



////////////////////////////////////////////////////////////////////

void Init_UART0(void)
{
   	PINSEL0|=0x00000005;
    U0LCR = 0X83;
    U0FDR = 177;
    U0DLM= 0;
    U0DLL =179;
    U0LCR = 0x03;
    U0FCR = 0x01;
    U0IER = 0x00000001;    //RI and TI interrupt
}


  void Init_UART1(void)
{
	PINSEL0|=0x00050000;
	U1FCR=0x07;
	U1FDR=177;
	U1LCR=0x83;
	U1DLL=179;
	U1DLM=0x00;
	U1LCR=0x07;
	U1IER = 0x00000003;    //RI and TI interrupt
}


void Init_VIC(void)
{
    VICIntSelect = 0x00000000;          //select timer0 interrupt ad IRQ i.e bit 4=0
    //VICIntEnClr =   0xFFFFFFFF;     // Diasable all interrupts
   // VICSoftIntClr = 0xFFFFFFFF;   // Clear all software interrutps
   // VICProtection = 0;              // VIC registers can be accessed in User or 

    VICVectCntl0 = 0x26;
    VICVectAddr0 = (unsigned long int)UART0ISR;
    VICIntEnable |= 0x00000040;          //enable UART0 interrupt


    VICVectAddr1 = (unsigned long int)UART1ISR;
    VICVectCntl1 = 0x27;       
    VICIntEnable |= 0x00000080;

}



    void UART0ISR(void)__irq
  {
    if(U0IIR & RDA)
    {
      while (!(U0LSR & 0x01));
      rxdat = U0RBR;
	  msg_read[k1]=rxdat;
      //msg_read[k1]=(rxdat&0x0f);
      k1++;
       if(k1==12)
       {
	   flag_u0=1;k1=0;delay_ms(2);
	   }  
    }
    VICVectAddr = 0x00;
}



  
    void UART1ISR(void)__irq
  {
    if(U1IIR & RDA)
    {
      while (!(U1LSR & 0x01));
      rxdat = U1RBR;
	  msg_read[k2]=rxdat;
      //msg_read1[k2]=(rxdat&0x0f);
      k2++;
       if(k2==12)
       {
	   flag_u1=1;k2=0;delay_ms(2);
	   }  
    }
    VICVectAddr = 0x00;
}


