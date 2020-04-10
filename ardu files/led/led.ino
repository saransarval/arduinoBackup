int led=13;
char ch;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(13,OUTPUT);
}

void loop() {
  
  
  // put your main code here, to run repeatedly:
  while(Serial.available()==0);

   ch=Serial.read();
   if(ch=='A')
   {
  Serial.println("A");
  digitalWrite(13,HIGH);
   }
 else if(ch=='B')
 {
   digitalWrite(13,LOW);
 }
}
