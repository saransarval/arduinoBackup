const int ap1 = A5; 
const int ap2 = A4;
const int ap3 = A3;
int l1=2;
int l2=3;
int sv1 = 0;        
int ov1 = 0;    
int sv2 = 0;      
int ov2= 0;      
int sv3 = 0;       
int ov3= 0;      
int a=0;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
 pinMode(13,OUTPUT);
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
}

void loop() {
  analogReference(EXTERNAL);    //connect 3.3v to AREF
  // read the analog in value:
  sv1 = analogRead(ap1);            
  // map it to the range of the analog out:
  ov1 = map(sv1, 0, 1023, 0, 255);  
  // change the analog out value:
                    
  //
  sv2 = analogRead(ap2);            
  
  ov2 = map(sv2, 0, 1023, 0, 255); 
 // 
                  
  //
  sv3 = analogRead(ap3);            
  
  ov3 = map(sv3, 0, 1023, 0, 255);  
  
  // print the results to the serial monitor:
 /* Serial.print("Xsensor1 = " );                       
  Serial.print(sv1);      
  Serial.print("\t output1 = ");      
  Serial.println(ov1);   
 
  Serial.print("Ysensor2 = " );                       
  Serial.print(sv2);      
  Serial.print("\t output2 = ");      
  Serial.println(ov2);   

  Serial.print("Zsensor3 = " );                       
  Serial.print(sv3);      
  Serial.print("\t output3 = ");      
  Serial.println(ov3);  */
if((ov1<=120)&&(ov2>=125)&&(ov3>=147))
{
 digitalWrite(2,HIGH);
Serial.println("1 ON");
}


else 
{
digitalWrite(2,LOW); 
}
if((ov1>=100)&&(ov2>=135)&(ov3<=128))
{
  Serial.println("2 On");
  digitalWrite(3,HIGH);
}
else
{
   digitalWrite(3,LOW);
} 
  delay(1000);                  
  
}
