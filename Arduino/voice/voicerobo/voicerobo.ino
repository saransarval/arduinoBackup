String voice;
int
m1 = 2, //Connect LED 1 To Pin #2
m2 = 3, //Connect LED 2 To Pin #3
m3 = 4, //Connect LED 3 To Pin #4
m4 = 5; //Connect LED 4 To Pin #5

//--------------------------Call A Function-------------------------------// 
void front()
{ 
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  Serial.println("STRAIGHT");
}
void right()
{
  Serial.println("RIGHT");
   digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  //delay(2000);
}
void left()
{
Serial.println("LEFT");
   digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}
void back()
{ 
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  Serial.println("BACKWARD");
}
void pause()
{ 
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  Serial.println("STOP");
}
//-----------------------------------------------------------------------// 
void setup() {
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  
}
//-----------------------------------------------------------------------// 
void loop() {
  while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = Serial.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  } 
  if (voice.length() > 0) {
    Serial.println(voice);

       if(voice == "*right") {right();}  
  else if(voice == "*left"){left();} 
 
  //----------Turn On One-By-One----------//
  else if(voice == "*back") {back();}
  else if(voice == "*front") {front();}
  else if(voice == "*stop") {pause();}
  
voice="";}} //Reset the variable after initiating

