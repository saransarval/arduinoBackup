int b1=2;
int b2=3;
int b3=4;
boolean flag1=0;
boolean flag2=0;
boolean flag3=0;
boolean pressed;
int a1,a2,a3;
unsigned char c=0;
float count;
float countc;
boolean d;
boolean a;
boolean e;
boolean f;
void setup()
{
    pinMode(b1, INPUT);//this time we will set the pin as INPUT
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
    count=1.5;
    countc=1;
}
void loop()
{

 a1=digitalRead(b1);
   
    a2= digitalRead(b2);
      a3 = digitalRead(b3);
      if(a2==LOW)
  {
    flag2=1;
  }
  if(a3==LOW)
  {
    flag3=1;
  }
  if(a1==LOW)
  {
    flag1=1;
  }
  if((a1==HIGH)&&(flag1==1)&&(c==0))
  {
    Serial.println("Calibration Mode......");
    delay(500);
    Serial.println("Please press the button for");
    Serial.println("\t 1.Voltage 2.Current 3.Temperature");
    flag1=0;
    c=1;
  }
    if((a1==HIGH)&&(flag1==1)&&(c==1))
    {
      Serial.println(" \t VOLTAGE CALIBRATION...");
      delay(500);
      Serial.println("Enter the actual value");
      delay(500);
      Serial.println("\t If value<1.5v please use Decrement key");
      delay(500);
      Serial.println("\t If value>1.5v please use Increment key");
      flag1=0;
      c=2;
     f=1;
    }
      
      if((a2==HIGH)&&(flag2==1)&&(c==2)&&(f==1))
  {
    count=count+0.01;
    Serial.println(count);
    flag2=0;
    d=1;
  }
  
  if((a3==HIGH)&&(flag3==1)&&(c==2)&&(f==1))
  {
    count=count-0.01;
    Serial.println(count);
    flag3=0;
    d=1;
  }
  if((a1==HIGH)&&(flag1==1)&&(d==1))
    {
      Serial.print("finalised voltage value is:");
      Serial.println(count);
      flag1=0;
  }
  
  if((a2==HIGH)&&(flag2==1)&&(c==1))
    {
      Serial.println(" \t CURRENT CALIBRATION...");
      delay(500);
      Serial.println("Enter the actual value");
      delay(500);
      Serial.println("\t If value<1A please use Decrement key");
      delay(500);
      Serial.println("\t If value>1A please use Increment key");
      flag2=0;
      c=2;
      d=2;
    }
    if((a2==HIGH)&&(flag2==1)&&(c==2)&&(d==2))
  {
    countc=countc+0.01;
    Serial.println(countc);
    flag2=0;
e=1;
  }
  if((a3==HIGH)&&(flag3==1)&&(c==2)&&(d=2))
  {
    countc=countc-0.01;
    Serial.println(countc);
    flag3=0;
 e=1;
  }
  if((a1==HIGH)&&(flag1==1)&&(e==1)&&(d==2))
    {
      Serial.print("finalised current value is:");
      Serial.println(countc);
      flag1=0;
      
  }
}
  

