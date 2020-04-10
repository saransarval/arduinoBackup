void setup() {
  // put your setup code here, to run once:
Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    delay(10000);
Serial.println("Alert ready to send");
delay(3000);
Serial.println("AT");
delay(1000);
Serial.println("AT+CMGF=1");
delay(1000);
Serial.println("AT+CMGS=\"+917200803616\"\r");
delay(1000);
Serial.println("!ALERT! ..Problem Found in Food Condition");// The SMS text you want to send
  delay(100);
   Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
Serial.println("AT+CMGD=1");
delay(1000);   //delete the message in sim location 1.
  }

}
