#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);
/*byte customchar[8] 
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};*/
void setup()
{
  lcd.begin(16,2);
  lcd.clear();
  /*lcd.createChar(1,customchar);
  lcd.print("Custom");*/
  //autoscroll//
  lcd.setCursor(0,0);
  lcd.print("Veron Techno Solution");
  lcd.setCursor(0,1);
  lcd.print("Coimbatore");
}
void loop()
{
///autoscroll//
lcd.setCursor(16,1);
lcd.print(" ");
lcd.autoscroll();
delay(500);
   ///string blinking//
/* lcd.setCursor(0,0);////(column,row)
  lcd.print("INFO");
  delay(1000);
 lcd.clear();
 delay(1000);*/
 //cursor blinking
/* lcd.setCursor(1,1);
   lcd.print("INFO");
  lcd.blink();
  delay(500);*/
  //custom character writer
  /*lcd.setCursor(1,1);
  lcd.write(1);*/
 
 
 
 
 
 
  

}
