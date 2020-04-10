#include <LiquidCrystal.h>
LiquidCrystal Lcd(12,11,5,4,3,2);

void setup() {
  // put your setup code here, to run once:
Lcd.begin(16,2);
Lcd.clear();

}

void loop() {
  // put your min code here, to run repeatedly:
Lcd.print("SARAN");

}
