char ch;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  while(1)
  {
  if(Serial.available())
  {

  ch=Serial.read();
   
  
  Serial.print(ch);
    }
  }
}                        
   
  
  

