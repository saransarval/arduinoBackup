char phone_no[]="7200803616";
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial1.begin(9600);
 delay(2000);
  Serial1.println("AT+CMGF=1");
  delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
 delay(1500);
    Serial.print("AT+CMGS=\"");
    Serial.print(phone_no);
    Serial.println("\"");
    char ch=Serial.read();
    if(ch==1);
     {
      String s="Switch on the motor";
      Serial1.print(s);
      delay(500);
      Serial.write(0x1A);
      Serial.write(0x0D);
      Serial.write(0x0A);
      delay(5000);
}
}
