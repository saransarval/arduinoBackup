int timesTosend=1;
int count=0;
char phone_no[]="7200803616";
void setup()
{
  Serial.begin(9600);
  delay(2000);
  Serial.println("AT+CMGF=1");
  delay(200);
}
void loop()
{
   int i=2345,j=1;
   int otp=1;
 // while(count<timesTosend)
 // {
    delay(1500);
    Serial.print("AT+CMGS=\"");
    Serial.print(phone_no);
    Serial.println("\"");
   // while(Serial.read()!='>');
     //{
      otp=otp+i+2-54*2/2;
      Serial.print(otp);
      delay(500);
      Serial.write(0x1A);
      Serial.write(0x0D);
      Serial.write(0x0A);
      delay(5000);
      //otp=otp/10;
    /// } 
   // count++;
  //}
}
    
