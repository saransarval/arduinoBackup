int sensor=A0;
int ldr=A1;
int led =13;
int sum;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
int a=analogRead(A0);
int b=analogRead(A1);
if(b>a)
{
  digitalWrite(13,HIGH);
  Serial.println("light on");  
}
else
{
  digitalWrite(13,LOW);
  Serial.println("light off");
}

}
  
}

