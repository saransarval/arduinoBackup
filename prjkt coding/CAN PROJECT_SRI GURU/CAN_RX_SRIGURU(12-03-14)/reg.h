

////////////CAN REGISTERS//////

int32 rx_id;
int in_data[8];
int rx_len;
//send a request (tx_rtr=1) for 8 bytes of data (tx_len=8) from id 24 (tx_id=24)
int rxstat;
int can_int_enable;
int Usart_buffer[9];
int usart_data_rx,  usart_cnt_data;
//////////////////////


void pic18f458_iniz()
 {
 portb=0;   
 trisb=0x08;  
 setup_adc_ports(NO_ANALOGS);
 ADCON1=0X07;//ADC OFF 
 CMCON=0X07;//COMPARATOR OFF
 enable_interrupts(INT_CANRX0);//enable interrupt,if CAN buffer full
 enable_interrupts(INT_RDA);  //usart interrupts
 enable_interrupts(global);
 }
