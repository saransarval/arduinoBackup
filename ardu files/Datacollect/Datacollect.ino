#include <Wire.h>  

unsigned char read_value[6];
unsigned char sign_temp=0;
unsigned char sign_volt=0;
unsigned char sign_current=0;

union RD_values//union concept for 16bit conversion
{
  uint16_t total_vlu;
  unsigned char rd_vlu[2]; 
}Total_read_value;

void setup() {
  Serial.begin(9600);
  Wire.begin();     // create a wire(i2c) object
}
 
void loop() {
  while(1)
  {
    int c1 = read_values();  // function for data reading from ic
   Serial.print("temp : ");
    
  
  Serial.println(read_value[1],HEX);//MSB
   Serial.println(read_value[0],HEX);//LSB
   Total_read_value.rd_vlu[0] = read_value[1];//16 bit conversion
   Total_read_value.rd_vlu[1] = read_value[0];//16 bit conversion
   //if()
   sign_temp = read_value[0] >> 7;//
   unsigned int a=((Total_read_value.total_vlu&0x7fff)>>5);//shifting 5 position
   Serial.println(a);
 

  Serial.print("vtg: ");
 // int c2 = read_vtg();  
  Serial.println(read_value[3],HEX);
  Serial.println(read_value[2],HEX);
  Total_read_value.rd_vlu[0] = read_value[3];
   Total_read_value.rd_vlu[1] = read_value[2];
   sign_volt = read_value[2] >> 7;
   unsigned int b=((Total_read_value.total_vlu&0x7fff)>>5);
   Serial.println(b);
 

  Serial.print("current: ");
 // int c3 = read_current();  
   Serial.println(read_value[5],HEX);
   Serial.println(read_value[4],HEX);
   Total_read_value.rd_vlu[0] = read_value[5];
   Total_read_value.rd_vlu[1] = read_value[4];
   sign_current = read_value[4] >> 7;
   unsigned int c=(Total_read_value.total_vlu&0x7fff);
   Serial.println(c);  
   
   delay(440);
}
}
 
int read_values() {
  
  unsigned int count;
  unsigned int c=0;
  //start the communication with  slave IC with the address 0x48
  Wire.beginTransmission(0x48); 
  //send a bit and ask for register zero
  Wire.write(0x0A);//request the data from slave with 0x0a
  //end transmission
  Wire.endTransmission();
  //request 1 byte from address xx
  Wire.requestFrom(0x48,6);//asking 6 bytes from slave
  //wait for response
  for(count=0; count<6;)
  {
    while(Wire.available() == 0);
    read_value[count] = Wire.read();//read 6 bytes read from slave
   
    count++;
    c = count;   
  }
  return c;//return count value
}


