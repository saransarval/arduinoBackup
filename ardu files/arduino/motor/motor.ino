int s1=6;
int s2=7;

int m1=2;
int m2=3;
int m3=4;
int m4=5;

void setup() {
  // put your setup code here, to run once:
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,INPUT);
pinMode(7,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

int a1=digitalRead(s1);
int a2=digitalRead(s2);
 if(a1==HIGH)
{
 digitalWrite(m1,HIGH);
digitalWrite(m2,LOW);
}
else
{
  digitalWrite(m1,LOW);
digitalWrite(m2,LOW); 
}
if(a2==HIGH)
{
   digitalWrite(m3,HIGH);
digitalWrite(m4,LOW);
}
else
{
   digitalWrite(m3,LOW);
digitalWrite(m4,LOW);
}

}
