
int D,D1,D2,D3,D4;
int g1=A0;
int g2=A1;
int g3=A2;
int g4=A3;
char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
void setup()
{
 pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
 DDRD=0xFF;
}
void loop()
{
  

for(int i=9999;i>=0;i--)
{
D1=i/1000;
D=i%1000;
D2=D/100;
D=D%100;
D3=D/10;
D4=D%10;
for(int f=0;f<=5000;f++);
digitalWrite(A0,HIGH);
PORTD=arr[D1];
delay (1000);
digitalWrite(A1,HIGH);
PORTD=arr[D2];
delay(1000);
digitalWrite(A2,HIGH);
PORTD=arr[D3];
delay(1000);
digitalWrite(A3,HIGH);
PORTD=arr[D4];
delay(1000);
}

}
