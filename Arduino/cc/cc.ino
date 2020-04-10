int led=13;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available()==0);
if(Serial.read()>0)
{
  char ch=Serial.read();
  if(ch=='1')
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
}
}
