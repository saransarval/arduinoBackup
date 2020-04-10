#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11);


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  while(1)
  {

     if (mySerial.available()) {
    char c =mySerial.read();

    Serial.print(c);
}
}
}
