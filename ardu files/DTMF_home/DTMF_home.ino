
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
 if((a==HIGH)&&(b==LOW)&&(c==LOW)&&(d==LOW))//1000//D0D1D2D3//1
  {
    Serial.println("LIGHT ON");
    digitalWrite(2,HIGH);
    
      }
      
   if((a==LOW)&&(b==HIGH)&&(c==LOW)&&(d==LOW))//0100//2
  {
   Serial.println("LIGHT OFF");
   digitalWrite(2,LOW);
    
  }
 if((a==HIGH)&&(b==HIGH)&&(c==LOW)&&(d==LOW))//1100//3
  {
    Serial.println("Fan ON");
    digitalWrite(3,HIGH);
   
  }
 
  if((a==LOW)&&(b==LOW)&&(c==HIGH)&&(d==LOW))//0010//4
  {
    Serial.println("Fan OFF");
      digitalWrite(3,LOW);
   
  }
  if((a==HIGH)&&(b==HIGH)&&(c==LOW)&&(d==HIGH))//1101//*
  {
    Serial.println("All ON");
       digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
   
  }
     if((a==LOW)&&(b==LOW)&&(c==HIGH)&&(d==HIGH))//0011//#
  {
    Serial.println("All OFF");
       digitalWrite(2,LOW);
        digitalWrite(3,LOW);
   
  }
}
  
