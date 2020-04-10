int b1=13;
int a;
int b=2;
void bling();
int s=284;
boolean flag1=0;
void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);
 //attachInterrupt(0,bling,RISING);
}
void loop()
{
a=digitalRead(b);
 if(a==LOW)
  {
    flag1=1;
  }
if((a==HIGH)&&(flag1==1))
{
  bling();
}
}
void bling()
{
  Serial.println("HAI");
  Serial.println("1st Value");
  while(Serial.available()==0);
  float ch= Serial.parseFloat();
      Serial.println(ch);
      Serial.println("2nd Value");
      while(Serial.available()==0);
      float c=Serial.parseFloat();
      Serial.println(c); 
      float v=s/c;
      Serial.println(v);
}

