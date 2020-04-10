#include <Adafruit_SleepyDog.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include "DHT.h"
#define DHTPIN 5 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
// nRF24L01(+) radio attached using Getting Started board 
RF24 radio(7,8);
 
// Network uses that radio
RF24Network network(radio);
 
// Address of our node
const uint16_t this_node = 2;
 
// Address of the other node
const uint16_t other_node = 0;
 
// How often to send 'hello world to the other unit
const unsigned long interval = 2000; //ms
 
// When did we last send?
unsigned long last_sent;
 
// How many have we sent already
unsigned long packets_sent;
 int a[32][3];
 int i,j;
 float h,t;
 long sensor;
// Structure of our payload
struct payload_t
{
  unsigned long ms;
  unsigned long counter;
};
void setup(void)
{
  Serial.begin(57600);
  Serial.println("RF24Network/examples/helloworld_tx/");
 dht.begin();
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
}
void loop(void)
{
  delay(2000);
  delay(2300);
  long sensor=analogRead(A0);
  float t = dht.readHumidity();
  float h = dht.readTemperature();
  float f = dht.readTemperature(true);
   
   
   if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Pump the network regularly
  network.update();
 
  // If it's time to send a message, send it!
  unsigned long now = millis();
  if ( now - last_sent >= interval  )
  {
    last_sent = now;
 
    Serial.print("Sending...");
    if(packets_sent> 94)
    {
    packets_sent=0;
    }  
    
    payload_t payload = { sensor, packets_sent++ };
    payload_t payload1={t,packets_sent++ };
    payload_t payload2={h,packets_sent++};
    RF24NetworkHeader header(/*to node*/ other_node);
    bool ok1 = network.write(header,&payload,sizeof(payload));
    delay(250);
    bool ok2 = network.write(header,&payload1,sizeof(payload1));
    delay(250);
    bool ok3 = network.write(header,&payload2,sizeof(payload2));
    delay(250);
    if(ok1)
    {
    if (ok2)
    {
    if(ok3)
      Serial.println("ok.");
     // Serial.println(&payload);
    }
    }
    else
      Serial.println("failed.");
  }
  
  for(int i=0;i<31;i++)
  {
   int j=0;
     while(j<=2)
     {
      long sensor=analogRead(A0);
      a[i][j]=sensor;
//      delay(250);
      j++;
      float t = dht.readHumidity();
      a[i][j]=t;
//      delay(250);
      j++;
      float h = dht.readTemperature();
      a[i][j]=h;
//      delay(250);
      j++;
     }
}

/*Serial.println("Going to sleep in one second...");
  delay(1000);
   int sleepMS = Watchdog.sleep();*/
   
}



