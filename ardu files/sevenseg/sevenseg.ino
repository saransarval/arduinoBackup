unsigned int num[11]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F},i,j,k;
int d1=A0;
int d2=A1;
int d3=A2;
int d4=A3;
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
  digitalWrite(A3,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A0,HIGH);
  for(k=0;k<6;k++)
  {
      PORTD=num[k];
    digitalWrite(A3,LOW);
    digitalWrite(A2,HIGH);
    digitalWrite(A1,LOW);
    digitalWrite(A0,LOW);
    delay(50);
  for(i=0;i<6;i++)
  {
    PORTD=num[i];
    digitalWrite(A3,LOW);
    digitalWrite(A2,LOW);
    digitalWrite(A1,HIGH);
    digitalWrite(A0,LOW); 
         delay(50);
    for(j=0;j<10;j++)
    {
      PORTD=num[j];
     
    digitalWrite(A0,HIGH); 
      delay(1000);
    }
  }
}
} 
