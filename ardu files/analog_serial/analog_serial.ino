
void setup()
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
  
}
void loop()
{
  
  while(1)
  {
 int a=analogRead(A0);
a=map( a,0,1023,0,255); 

 Serial.println(a);
 delay(500);
  }
}
