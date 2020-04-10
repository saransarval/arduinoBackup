char  c[16],i,j;
String s;
String stringOne = String("OPEN=hari");
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.print("start");
s="";
}

void loop() {  
  // put your main code here, to run repeatedly:
if(Serial.available()>0)
{
i=Serial.read();
s+=i;
}
if(s=="OPEN=hari")
{
 Serial.print( s);
 s="";
 Serial.println("password received......");
 delay(2000);
 Serial.println("The OTP will send your registered mobile no");

}

Serial.flush();

}
