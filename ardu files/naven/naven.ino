//gesture.ino
const int ap1 = A0; 
const int ap2 = A1;
int sv1 = 0;        
int ov1 = 0;    
int sv2 = 0;      
int ov2= 0;  
void setup()
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
}
void loop() 
{
  analogReference(EXTERNAL);    //connect 3.3v to AREF
  // read the analog in value:
  sv1 = analogRead(ap1);            
   ov1 = map(sv1, 0, 1023, 0, 255);  
  delay(100);                     
  sv2 = analogRead(ap2);            
 ov2 = map(sv2, 0, 1023, 0, 255); 
    delay(100);                 

  Serial.print("Xsensor1 = " );                       
  Serial.print(sv1);      
  Serial.print("\t output1 = ");      
  Serial.println(ov1);   

  Serial.print("Ysensor2 = " );                       
  Serial.print(sv2);      
  Serial.print("\t output2 = ");      
  Serial.println(ov2);   

//  if(analogRead (355>(ap1)>345) &&analogRead (455>(ap2)>445)) // for backward movement 
//  {
//    Serial.println("Back");
//    digitalWrite(13,HIGH);
//    digitalWrite(12,LOW);
//    digitalWrite(11,HIGH);
//    digitalWrite(10,LOW);
//  }
//  else
//  {
//    if(analogRead (415>(ap1)>400) &&analogRead (435>(ap2)>425)) // for left turn
//    {
//      Serial.println("Left");
//      digitalWrite(13,LOW);
//      digitalWrite(12,HIGH);
//      digitalWrite(11,HIGH);
//      digitalWrite(10,LOW);
//    }
//    else
//    {
//      if(analogRead (525>(ap1)>515) &&analogRead (445>(ap2)>435)) // for forward
//      {
//        Serial.println("Forward");
//        digitalWrite(13,LOW);
//        digitalWrite(12,HIGH);
//        digitalWrite(11,LOW);
//        digitalWrite(10,HIGH);
//      }
//      else
//      {
//        if(analogRead (435>(ap1)>425) &&analogRead (475>(ap2)>465))//for right turn
//        {
//          Serial.println("Right");
//          digitalWrite(13,HIGH);
//          digitalWrite(12,LOW);
//          digitalWrite(11,LOW);
//          digitalWrite(10,HIGH);
//        }
//
//        else
//        {
//          digitalWrite(13,HIGH);
//          digitalWrite(12,HIGH);
//          digitalWrite(11,HIGH);
//          digitalWrite(10,HIGH);
//        }
//      }
//    }
//  }
}

