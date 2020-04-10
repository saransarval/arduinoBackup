#include <TimeLib.h>
unsigned char l1=2;
unsigned char l2=3;
unsigned char l3=4;
unsigned char l4=5;
unsigned char l5=6;
unsigned char l6=7;
unsigned char l7=8;
unsigned char l8=9;
unsigned char l9=10;
unsigned char l10=11;
unsigned char l11=12;
unsigned char l12=13;
unsigned char l13=A0;
unsigned char l14=A1;
void setup()  {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
 
  setTime(11,30,30,12,02,2016);
}

void loop(){    
     now();
  byte sec=second();
  byte mini=minute();
  byte hr=hour();
  float delaytimes=0.63*sec;
  float dtimem=0.63*mini;
  float dtimehr=0.63*hr;
 //Serial.print(sec);
    Serial.println(" ");
   //Serial.print(); 
    delay(1000);

    seconds_display();
    delayMicroseconds(delaytimes);
    minuites_display();
    delayMicroseconds(dtimem);
    hr_display();
    delayMicroseconds(dtimehr);
}

void hr_display()
{
  digitalWrite(2,HIGH);
   digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
     digitalWrite(5,HIGH);
      digitalWrite(10,HIGH);
       digitalWrite(11,HIGH);
 digitalWrite(6,LOW);   
 digitalWrite(7,LOW); 
 digitalWrite(8,LOW); 
 digitalWrite(9,LOW); 
 digitalWrite(12,LOW); 
 digitalWrite(13,LOW); 
 digitalWrite(A0,LOW); 
 digitalWrite(A1,LOW);  
    }
void minuites_display()
{
 digitalWrite(2,HIGH);
   digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
     digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
       digitalWrite(7,HIGH); 
       digitalWrite(12,HIGH); 
      digitalWrite(13,HIGH);  
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(A0,LOW); 
 digitalWrite(A1,LOW);          
}
void seconds_display()
{
digitalWrite(2,HIGH);
   digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
     digitalWrite(5,HIGH); 
     digitalWrite(6,HIGH);
       digitalWrite(7,HIGH); 
        digitalWrite(8,HIGH); 
        digitalWrite(9,HIGH);  
        digitalWrite(A0,HIGH); 
        digitalWrite(A1,HIGH);
digitalWrite(10,LOW);
digitalWrite(11,LOW);
digitalWrite(12,LOW); 
digitalWrite(13,LOW);           
}

