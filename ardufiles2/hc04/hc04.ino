#define echopin 6
#define trigpin 7
int led=13;
long duration,distance;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(6,INPUT);

pinMode(7,OUTPUT);
pinMode(13,OUTPUT);
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
Serial.println(distance);
Serial.print("cm");
analogWrite(13,distance);
}
