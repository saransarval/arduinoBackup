// Import libraries (BLEPeripheral depends on SPI)
#include <SPI.h>
#include <BLEPeripheral.h>

//////////////
// Hardware //
//////////////
#define LED_PIN    7 // LED on pin 7
#define LED_ACTIVE LOW // Pin 7 LED is active low
#define LED_DEFAULT LOW

///////////////////////
// BLE Advertisments //
///////////////////////
const char * localName = "nRF52832 LED";
unsigned short state=10;
unsigned short state1=20;
unsigned short state2=30;
BLEPeripheral blePeriph;
BLEService bleServ("1207");
BLECharCharacteristic ledChar("1207", BLEWrite | BLENotify);

void setup() 
{
  Serial.begin(115200); // Set up serial at 115200 baud

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, !LED_ACTIVE);

  setupBLE();
}

void loop() 
{
  blePeriph.poll();
delay(500);
  if (ledChar.written())
  {
    int ledState = ledChar.value();
    if (ledState==1)
    {
        ledChar.setValue(state);
        // state++;
      digitalWrite(LED_PIN, LED_ACTIVE);
    }
    else if(ledState==2)
    {
     ledChar.setValue(state1); 
    }
      else if(ledState==3)
    {
     ledChar.setValue(state2); 
    }
    else
      digitalWrite(LED_PIN, !LED_ACTIVE);
      
  }
 
 
}

void setupBLE()
{
  // Advertise name and service:
  blePeriph.setDeviceName(localName);
  blePeriph.setLocalName(localName);
  blePeriph.setAdvertisedServiceUuid(bleServ.uuid());

  // Add service
  blePeriph.addAttribute(bleServ);

  // Add characteristic
  blePeriph.addAttribute(ledChar);

  // Now that device6, service, characteristic are set up,
  // initialize BLE:
  blePeriph.begin();

  // Set led characteristic to default value:
  //ledChar.setValue(!LED_ACTIVE);  
  ledChar.setValue(state);
}

