String com;
char ch;
int led=13;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available())
{
  delay(10);
  ch=Serial.read(); 
  if (ch == '#') {break;}   
    com+=ch;
    }
    
  
  if(com.length()>0)
  {
       Serial.println(com);
    if(com=="*fanon")
    {
      digitalWrite(13,HIGH);
    }
    else if(com=="*fanoff")
    {
      digitalWrite(13,LOW);
    }
    }
 com="";
  }



