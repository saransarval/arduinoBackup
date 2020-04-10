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
int led=10;
int led1=2;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(10,OUTPUT);
  pinMode(2,OUTPUT);
  // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
   // Serial.println(results.value, HEX); 
   if(results.value==0x2FD807F)
   {
    if(c==0)
    {   
      Serial.println(results.value, HEX);
      digitalWrite(10,HIGH);
      c=1;
    }
    else
    {
     digitalWrite(10,LOW);  
     c=0;
    }
   }
   if(results.value==0x2FD40BF)
   {
    if(d==0)
    {
      Serial.println(results.value, HEX);
      
     digitalWrite(2,HIGH);
      d=1;
    }
    else
    {
     digitalWrite(2,LOW);  
     d=0;
    }
   }
    irrecv.resume(); // Receive the next value
  }
}
