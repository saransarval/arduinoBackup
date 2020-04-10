int button=3;
int led=13;
int flag1=0;
void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
pinMode(3,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int b=digitalRead(3);
if(b==LOW)
{
  flag1=1;
}
if((b==HIGH)&&(flag1==1))
{
  Serial.print("LED ON");
  digitalWrite(13,HIGH);
  delay(2000);
  flag1=0;
}
else
{
  digitalWrite(13,LOW);
}
}
