boolean currentState = LOW;//stroage for current measured button state
boolean lastState = LOW;//storage for last measured button state
boolean debouncedState = LOW;//debounced button state

int debounceInterval = 20;//wait 20 ms for button pin to settle
unsigned long timeOfLastButtonEvent = 0;//store the last time the button state changed
int buttonPin=2;
void setup(){
  pinMode(buttonPin, INPUT);//this time we will set the pin as INPUT
  Serial.begin(9600);//initialize Serial connection
}

void loop(){
  
  currentState = digitalRead(buttonPin);
  unsigned long currentTime = millis();
  
  if (currentState != lastState){
    timeOfLastButtonEvent = currentTime;
  }
  
  if (currentTime - timeOfLastButtonEvent > debounceInterval){//if enough time has passed
    if (currentState != debouncedState){//if the current state is still different than our last stored debounced state
      debouncedState = currentState;//update the debounced state
      
      //trigger an event
      if (debouncedState == HIGH){
        Serial.println("pressed");
      } 
      /*else {
        Serial.println("released");
      }*/
    }
  }
  
  lastState = currentState;
}
