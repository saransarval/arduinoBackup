#include <Wire.h>
unsigned char address1 = 0x01;  //decimal address of sensor 1
//unsigned char address2 = 11;  //decimal address of sensor 2
 
void setup() {
  Serial.begin(9600);
  Wire.begin();     // create a wire object
}
 
void loop() {
  while(1)
  {
   
  int c1 = read_temp(address1);
  //int c2 = read_temp(address2);  
  Serial.println("tempreg 1: ");
  Serial.println(c1,HEX);

  //Serial.print("tempreg 2: ");
  //Serial.print(c2);
  //Serial.print("C | ");
  delay(440);  
}
}
 
int read_temp(int address) {
  //start the communication with IC with the address xx
  Wire.beginTransmission(0x48); //slave address 
  
  Wire.write(0x01);//request Temperature register
  
  //end transmission
  Wire.endTransmission();
  //request 1 byte from slave with address xx 
  Wire.requestFrom(0x48,1);
  //wait for response
  while(Wire.available() == 0);
  //put the temperature in variable c
  int c = Wire.read();   
  
  
  return c;
}
