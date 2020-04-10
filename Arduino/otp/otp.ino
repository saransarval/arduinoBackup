#include<LiquidCrystal.h>
#include <extern.h>
LiquidCrystal lcd(4,5,6,7,8,9);
const int SeedPin=A0;
const int button=2;
int buttonState;
int prevButtonState;
int totalNumbersGenerated=0;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(SeedPin,INPUT);
  pinMode(button,INPUT);
  int randSeed=analogRead(SeedPin);
  int GeneratedSeed=random(-randSeed,randSeed);
  randomSeed(GeneratedSeed);
  prevButtonState=digitalRead(button);
 // PrintToLcd( "Rng:"+String(-randSeed)+"-"+String(randSeed),"Seed:"+String(GeneratedSeed));
}
void loop()
{
  while(Serial.available()==0);
  if(Serial.read()>0)
  {
  char ch=Serial.read();
  if(ch=='A')
  {
  
  /*buttonState=digitalRead(button);
  if(buttonState!=prevButtonState && buttonState==HIGH)
  {*/
    totalNumbersGenerated++;
    PrintToLcd(
    "Result#"+String(totalNumbersGenerated),
    String(random(-999999999,999999999)));
    delay(100);
    delaysec();
  }
  }
  }
  //prevButtonState=buttonState;

void PrintToLcd (String line1,String line2)
{
  lcd.clear();
  Serial.println(line1);
  lcd.setCursor(0,1);
  Serial.println(line2);
}
