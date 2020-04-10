#include <SoftwareSerial.h>
SoftwareSerial zigbee(2,3); // RX, TX
char sensor;
int sen;
String  s;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 while(1)
{
 for(int j=0;j<3;j++)
  {
    for(int k=0;k<10;k++)
    {
  for(int i=0;i<2;i++)
  {
 sensor=Serial.read();
  s=s+sensor;


 delay(500);
  }
  Serial.println(s);
  s="";
   
  delay(1000);
    }
  }
}
}
