char d1,d2,d3;
char c1,c2,c3;
int soil=A0;
int soil_read;
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
RF24 radio(9,10);
RF24Network network(radio);
const uint16_t this_node = 1;// Address of our node
const uint16_t other_node = 0;
const unsigned long interval = 2000; //ms
unsigned long last_sent;
struct payload_t
{
  unsigned long ms;
  unsigned long counter;
};
void setup() {
  // put your setup code here, to run once:

  Serial.begin(57600);
  dht.begin();
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
  pinMode(A0,INPUT); 
}

void loop() {
  while(1)
  {
  // put your main code here, to run repeatedly:
   delay(2000);
   soil_read=analogRead(A0);
 float h = dht.readHumidity();
   float t = dht.readTemperature();
    network.update();
    unsigned long now = millis();
  if ( now - last_sent >= interval  )
  {
    last_sent = now;
    Serial.print("Sending...");
    payload_t payload = { h,t, };
//    payload_t payload = { t };
    RF24NetworkHeader header(/*to node*/ other_node);
    //bool ok = network.write(header,&payload,sizeof(payload));
    //if (ok)
      Serial.println("ok.");
  
  }
  Serial.print("Soil status");
  Serial.print(soil_read);
   Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
 // char ch[9] ={2,d,0,3};
}
}
