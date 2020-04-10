
void straight();
void right();
void left();
void back();
void pause();

int m1=2;
int m2=3;
int m3=4;
int m4=5;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

if(Serial.available()>0)
{
 char ch=Serial.read();
  switch(ch)
  {
    case 'f':straight();break;
    case 'd':back(); break;
    case 'r':right();break;
    case 'l':left();break;
    case 'p':pause();break;
    default :break;
  }
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

