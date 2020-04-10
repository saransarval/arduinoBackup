int b1=2;
int b2=3;
int b3=4;
int a1,a2,a3;
int led=13;
void setup()
{
  pinMode(13,OUTPUT);
  pinMode(a1,INPUT);
  pinMode(a2,INPUT);
  pinMode(a3,INPUT);
}
void loop()
{
  a1=digitalRead(b1);
  a2=digitalRead(b2);
  a3=digitalRead(b3);
  if(a1==HIGH)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  
  if(a2==HIGH)
  {
    int i=0;
    while(i<100)
    {
      digitalWrite(13,HIGH);
    delay(200);
    digitalWrite(13,LOW);
    i++;
    }
  }
  else
  {
    digitalWrite(13,LOW);
  }
  if(a3==HIGH)
  {
      int i=0;
    while(i<100)
    {
      digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    i++;
    }
  }
else
  {
    digitalWrite(13,LOW);
  }
}

