int b1=2;
int b2=3;
int b3=4;
boolean flag1=0;
boolean flag2=0;
boolean flag3=0;
boolean pressed;
int a1,a2,a3;
void setup()
{
    pinMode(b1, INPUT);//this time we will set the pin as INPUT
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  a1=digitalRead(b1);
   
    a2= digitalRead(b2);
      a3 = digitalRead(b3);
  if(a1==LOW)
  {
    flag1=1;
  }
  if((a1==HIGH)&&(flag1==1))
  {
    Serial.println("1st pressed");
    flag1=0;
  }
  if(a2==LOW)
  {
    flag2=1;
  }
  if((a2==HIGH)&&(flag2==1))
  {
    Serial.println("2nd button pressed");
    flag2=0;
  }
  if(a3==LOW)
  {
    flag3=1;
  }
  if((a3==HIGH)&&(flag3==1))
  {
    Serial.println("3rd button pressed");
    flag3=0;
  }
}
