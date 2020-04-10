void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
Serial.println("AT+CMGF=1");
Serial.println("AT+CSTT=www");
Serial.println("AT+CSTT=imis/internet");
Serial.println("AT+CIICR");
Serial.println("AT+CIFSR");
//Serial.print("AT+CIPSTART=","TCP","GOOGLE.CO.IN","80"");
Serial.print("TCP");
Serial.print("google.co.in");
Serial.println("1234");
Serial.println("AT+CIPSEND");

}

void loop() {
  // put your main code here, to run repeatedly:
while(1)
{
}
}

