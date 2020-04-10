
int d0=6;
int d1=7;
int d2=8;
int d3=9;
int m1=2;
int m2=3;
int m3=4;
int m4=5;


void setup() {
  // put your setup code here, to run once:
pinMode(6,INPUT);
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(9,INPUT);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a=digitalRead(6);
    int b=digitalRead(7);
      int c=digitalRead(8);
        int d=digitalRead(9);
  if((a==LOW)&&(b==HIGH)&&(c==LOW)&&(d==LOW))
  {
    //Serial.println("Forward");
    straight();
      }
   if((a==LOW)&&(b==LOW)&&(c==LOW)&&(d==HIGH))
  {
   // Serial.println("Backward");
    back();
  }
 if((a==LOW)&&(b==LOW)&&(c==HIGH)&&(d==LOW))
  {
    //Serial.println("LEFT");
    left();
  }
  if((a==LOW)&&(b==HIGH)&&(c==HIGH)&&(d==LOW))
  {
    //Serial.println("Right");
    right();
  }
  if((a==LOW)&&(b==HIGH)&&(c==LOW)&&(d==HIGH))
  {
    //Serial.println("STOP");
    pause();
  }
  
  }
  void straight()
{ 
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  Serial.println("STRAIGHT");
}
void right()
{
  Serial.println("RIGHT");
   digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  //delay(2000);
}
void left()
{
Serial.println("LEFT");
   digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}
void back()
{ 
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  Serial.println("BACKWARD");
}
void pause()
{ 
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  Serial.println("STOP");
}


