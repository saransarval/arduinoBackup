#define echopin 6
#define trigpin 7
void straight();
void right();
int led=13;
int m1=2;
int m2=3;
int m3=4;
int m4=5;
long duration,distance;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(6,INPUT);

pinMode(7,OUTPUT);
pinMode(13,OUTPUT);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(7,LOW);
delayMicroseconds(2);
digitalWrite(7,HIGH);
delayMicroseconds(10);
digitalWrite(7,LOW);
duration=pulseIn(6,HIGH);
distance=duration/29.1/2;
//Serial.println(distance);
//Serial.print("cm");
if(distance>=5&&distance<=35)
{
  right();
  straight();
}
else
{
  straight();

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
  delay(500);
}

