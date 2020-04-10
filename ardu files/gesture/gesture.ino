const int ap1 = A5; 
const int ap2 = A4;
const int ap3 = A3;
int l1=2;
int l2=3;
int l3=4;
int l4=5;
int sv1;        
int ov1 = 0;   
int sv2;      
int ov2= 0;      
int sv3 = 0;       
int ov3= 0;      

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
 pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
   pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
}

void loop() {
  analogReference(EXTERNAL);    //connect 3.3v to AREF
  // read the analog in value:
  sv1 = analogRead(ap1);            
  // map it to the range of the analog out:
  ov1 = map(sv1, 0, 1023, 0, 255);  
  // change the analog out value:
  delay(2);                     
  //
  sv2 = analogRead(ap2);            
  
  ov2 = map(sv2, 0, 1023, 0, 255); 
 // 
  delay(2);                 
  //
  sv3 = analogRead(ap3);            
  
  ov3 = map(sv3, 0, 1023, 0, 255);  
  
 /* // print the results to the serial monitor:
  Serial.print("Xsensor1 = " );                       
  Serial.print(sv1);      
  Serial.print("\t output1 = ");      
  Serial.println(ov1);   
  //delay(1000);
 
  Serial.print("Ysensor2 = " );                       
  Serial.print(sv2);      
 Serial.print("\t output2 = ");      
  Serial.println(ov2);  
delay(1000);*/
 /* Serial.print("Zsensor3 = " );                       
  Serial.print(sv3);      
  Serial.print("\t output3 = ");      
  Serial.println(ov3); */  

  //delay(1000);                     
  if(sv1>=485&&sv1<=500)
  {
    Serial.println(" LEFT");
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }
  else
  {
  digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
}
  if(sv1>=584&&sv1<=604)
  {
    Serial.println(" FRONT");
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }
  else
  {
  digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
}
  
  if(sv1>=418&&sv1<=438)
  {
    Serial.println("Back");
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    //digitalWrite(13,HIGH);
  }
  else
  {
  digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
}
  
  if(sv1>=530&&sv1<=550)
  {
    Serial.println(" RIGHT");
    //digitalWrite(13,HIGH);
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
   else
  {
  digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
}
  
}
