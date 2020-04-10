int led=13;
int sw=2;
int flag=0;
int count=0;
void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);  
  // put your setup code here, to run once:

}

void loop() 
{
  int a=digitalRead(2);
  
    while(1);
    {
      if(a==HIGH&&flag==0)
      {
        flag=1;
        count=flag+count;
        digitalWrite(13,HIGH);
        Serial.println(count);
      }
      else
      {
        flag=0;
        digitalWrite(13,LOW);
        Serial.println("LED OFF");
      }
    
      }
    
 
  // put your main code here, to run repeatedly:

}
