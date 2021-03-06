/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;
int c=0;
int d=0;
int led=13;
int led1=2;
int steps=0;
int bright;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(13,OUTPUT);
  pinMode(2,OUTPUT);
  // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
   // Serial.println(results.value, HEX); 
  
   
    irrecv.resume(); // Receive the next value
  }
}
