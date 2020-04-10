/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <EEPROM.h>
#include <IRremote.h>
uint32_t rx;
int RECV_PIN = 11;
int addr = 0; 
unsigned char buf[10];
IRrecv irrecv(RECV_PIN);

decode_results results;
int c=0;
int d=0;
int led=13;
int led1=2;
int i=0;
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
   Serial.println(results.value, HEX); 
   rx=results.value;



   
  Serial.println("please enter the button to on light1"); 
    buf[i]=rx>>24;
    buf[i+1]=rx>>16;
    buf[i+2]=rx>>8;
    buf[i+3]=rx;
    i=i+4;
   }
    EEPROM.write(addr, rx>>24);
    
   Serial.println("rx value");
  uint32_t  value = EEPROM.read(addr);
   Serial.println(value, HEX);
    irrecv.resume(); // Receive the next value
  }
}
