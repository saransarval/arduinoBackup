boolean cs1 = LOW;//stroage for current measured button state
boolean cs2 = LOW;
boolean cs3 = LOW;
boolean ls1 = LOW;//storage for last measured button state
boolean ls2 = LOW;
boolean ls3 = LOW;
boolean dbs1 = LOW;//debounced button state
boolean dbs2= LOW;
boolean dbs3= LOW;
int led1=13;
int led2=6;
int led3=7;
int debounceInterval = 20;//wait 20 ms for button pin to settle
unsigned long tlb1 = 0;//store the last time the button state changed
unsigned long tlb2= 0;
unsigned long tlb3 = 0;
int b1=2;
int b2=3;
int b3=4;
void setup(){
  pinMode(b1, INPUT);//this time we will set the pin as INPUT
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(13,OUTPUT);
  
  Serial.begin(9600);//initialize Serial connection
}

void loop(){
  
  cs1 = digitalRead(b1);
    cs2 = digitalRead(b2);
      cs3 = digitalRead(b3);
  unsigned long currentTime = millis();
  
  if (cs1 != ls1){
    tlb1= currentTime;
  }
  if(cs2!=ls2)
  {
     tlb2= currentTime;
  }
   if(cs3!=ls3)
  {
     tlb3= currentTime;
  }
  
  if (currentTime - tlb1 > debounceInterval){//if enough time has passed
    if (cs1 !=dbs1){//if the current state is still different than our last stored debounced state
      dbs1 =cs1;//update the debounced state
      
      //trigger an event
      if (dbs1 == HIGH){
        Serial.println("1st pressed");
        digitalWrite(13,HIGH);
      } 
      else {
        digitalWrite(13,LOW);
      }
    }
  }
  if (currentTime - tlb2 > debounceInterval){//if enough time has passed
    if (cs2!=dbs2){//if the current state is still different than our last stored debounced state
      dbs2 =cs2;//update the debounced state
      
      //trigger an event
      if (dbs2 == HIGH){
        Serial.println("2nd button pressed");
        digitalWrite(6,HIGH);
      } 
      else {
        digitalWrite(6,LOW);
      }
    }
  }
  if (currentTime - tlb3 > debounceInterval){//if enough time has passed
    if (cs3 !=dbs3){//if the current state is still different than our last stored debounced state
      dbs3 =cs3;//update the debounced state
      
      //trigger an event
      if (dbs3 == HIGH){
        Serial.println("3rd button pressed");
        digitalWrite(7,HIGH);
      } 
      else {
        digitalWrite(7,LOW);
      }
    }
  }
  ls1 =cs1;
  ls2=cs2;
  ls3=cs3;
}
