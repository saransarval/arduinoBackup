#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);
int an= A0;
void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
lcd.clear();
pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
while(1)
{
int a=analogRead(A0);
int val=map(a,0,1023,0,255);
lcd.setCursor(0,0);
lcd.print("Analog Read");
lcd.setCursor(1,1);
lcd.print(val);
}
}
