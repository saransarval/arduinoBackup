#include "SoftwareSerial.h"
//#include "OneWire.h"
//#include "DallasTemperature.h"

SoftwareSerial lora(3, 4); // RX, TX
// OneWire bus pin for temperature sensor pin
//#define ONE_WIRE_BUS 6
// Setup a oneWire instance to communicate with any OneWire devices
//OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
//DallasTemperature sensors(&oneWire);

// arrays to hold device address
//DeviceAddress temperatureSensor;
float temperature;
void sendCmd( char *cmd) {
  Serial.write( cmd );
  Serial.write("\n");
  lora.write(cmd);
  lora.write("\r\n");
  while (!lora.available() ) {
    delay(100);
  }
  while (lora.available())
    Serial.write(lora.read());
}

void waitForResponse() {
  while (!lora.available() ) {
    delay(100);
  }
  while (lora.available())
    Serial.write(lora.read());
}

char getHexHi( char ch ) {
  char nibble = ch >> 4;
  return (nibble > 9) ? nibble + 'A' - 10 : nibble + '0';
}
char getHexLo( char ch ) {
  char nibble = ch & 0x0f;
  return (nibble > 9) ? nibble + 'A' - 10 : nibble + '0';
}

void sendData( char *data) {
  Serial.write( "mac tx uncnf 1 " );
  lora.write( "mac tx uncnf 1 " );
  // Write data as hex characters
  char *ptr = data;
  int idiotCount = 50;
  while (*ptr && idiotCount ) {
    lora.write( getHexHi( *ptr ) );
    lora.write( getHexLo( *ptr ) );

    Serial.write( getHexHi( *ptr ) );
    Serial.write( getHexLo( *ptr ) );

    ptr++;
    idiotCount--;
  }
  lora.write("\r\n");
  Serial.write("\n");
  delay(2000);

  while (lora.available())
    Serial.write(lora.read());
}

void setup()
{
   //float temperature;;
  Serial.begin(57600);
  lora.begin(57600);
  Serial.println("RN2483 Test");

  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  delay(50);
  digitalWrite(5, LOW);
  delay(50);
  digitalWrite(5, HIGH);
  delay(50);

 waitForResponse();

  /*sensors.begin();
  if (sensors.getAddress(temperatureSensor, 0)) {
    // set the resolution to 9 bit
    sensors.setResolution(temperatureSensor, 9);
  }
*/
  sendCmd("sys factoryRESET");
  sendCmd("sys get hweui");
  sendCmd("mac get deveui");

  // For TTN
  sendCmd("mac set devaddr AABBCCDD");  // Set own address
  sendCmd("mac set appskey 2B7E151628AED2A6ABF7158809CF4F3C");
  sendCmd("mac set nwkskey 2B7E151628AED2A6ABF7158809CF4F3C");
  sendCmd("mac set adr off");
  sendCmd("mac set rx2 3 869525000");
  sendCmd("mac join abp");
  sendCmd("mac get status");
  sendCmd("mac get devaddr");
 
}

void loop() {
  // put your main code here, to run repeatedly:
  

 // sensors.requestTemperatures();
  temperature++;
  Serial.println(temperature);
  char msgBuf[40];
  sprintf(msgBuf, "{\"temp\":%d.%01d}", (int)temperature, (int)(temperature * 10) % 10);
  Serial.println(msgBuf);

  sendData(msgBuf);
  delay(5000);
  while (lora.available())
    Serial.write(lora.read());

  delay(2000);
  temperature++;
}

