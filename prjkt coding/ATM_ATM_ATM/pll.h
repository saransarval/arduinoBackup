	
#define PLOCK (1<<10)
#define PLLE   1   ////	PLL ENABLE BIT
#define PLLC   2   //// PLL ConnectION BIT

void lpc2148_pll(void);	
void lpc2148_pll(void)
{
        PLL0CFG      = 0x24; ////p=2,m=5//                          
        PLL0CON      = PLLE;                                    
        PLL0FEED     = 0xAA;                                  
        PLL0FEED     = 0x55;

        while (((PLL0STAT & PLOCK) == 0));
		 
        PLL0CON      = PLLE|PLLC;                                   
        PLL0FEED     = 0xAA;                                  
        PLL0FEED     = 0x55;
        VPBDIV       = 0x02; //   VP BUS SYSTEM =CLOCL  /VPBDIV 
}
