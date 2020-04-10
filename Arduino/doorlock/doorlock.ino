#include <LiquidCrystal.h>
#include <Keypad.h>
LiquidCrystal lcd(12,11,5,4,3,2);
char*secretCode="1316";
int v=0;
int x=6;
int z=0;
int p=0;
int position=0;
const byte rows = 4;
const byte cols = 3;
char keys[rows][cols]=
{
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}
};
byte rowPins[rows]={A5,A4,A3,A2};
byte colPins[cols]={A1,A0,8};
Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,rows,cols);
int ledPin=10;
int vishPin=9;
int yPin=6;
void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(vishPin,OUTPUT);
  pinMode(yPin,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(13,OUTPUT);
  setLocked(true);
}
void loop()
{
 char key=keypad.getKey();
 if(key)
{
  digitalWrite(ledPin,HIGH);
  delay(100);
  digitalWrite(ledPin,LOW);
     if(key=='*' || key=='#'){}
     else
    {
      lcd.setCursor(0,0);
      lcd.print("Max. 4 digit pls");
      lcd.setCursor(0,1);
      lcd.print("------____------");
      lcd.setCursor(x,1);
      x++;
      lcd.print("*");
      v++;
  }  
}
if(key=='#')
{
  position=0;
}

if(key==secretCode[position])
 {
   position++;
 }

if(position==4 && v==4)
   {
     setLocked(false);
   }
if(position!=4 && v==4)
{
   wrongOk(true);
}
delay(100);
if(key=='*')
{
 setLocked(true);
}

}

void setLocked(int locked)
{
  if(locked)
{
  if(x != 6)
  {
    x=6;
  }
 if(v != 0)
  {
    v=0;
  }
digitalWrite(vishPin,HIGH);
digitalWrite(yPin,LOW);
lcd.begin(16,2);
lcd.setCursor(0,1);
lcd.print("LOCKING THE DOOR");
delay(2000);
if(p==1)
{
  digitalWrite(7,HIGH);
  digitalWrite(13,LOW);
  delay(1000);
   digitalWrite(7,LOW);
     digitalWrite(13,LOW);
  p--;

}
lcd.clear();
lcd.setCursor(0,0);
lcd.print("*V & N Ptd Ldt*");
lcd.setCursor(0,1);
lcd.print("~ WELCOMES YOU ~");
delay(3000);
lcd.setCursor(0,0);
lcd.print(" ENTER PASSWORD ");
lcd.setCursor(0,1);
lcd.print("TO OPEN THE DOOR");

}
  else
{
   if(x != 6)
     {
       x=6;
     }
    if(v != 0)
  {
    v=0;
  }
     digitalWrite(vishPin,LOW);
     digitalWrite(yPin,HIGH);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("**** ACCESS ****");
     lcd.setCursor(0,1); 
     lcd.print("*** GRANTED ****");
     delay(2000);
     digitalWrite(7,LOW);
     digitalWrite(13,HIGH);
     delay(1000);
     digitalWrite(7,LOW);
     digitalWrite(13,LOW);
     p++;
     lcd.setCursor(0,0);
     lcd.print(" Press # than * ");
     lcd.setCursor(0,1);
     lcd.print("to Lock the door");
}

}
void wrongOk(int ok)
{
  if(v != 0)
  {
    v=0;
  }
  if(ok)
   {
     for(int v=0 ; v<10 ; v++)
        {
          digitalWrite(vishPin,HIGH);
          delay(150);
          digitalWrite(vishPin,LOW);
          digitalWrite(ledPin,HIGH);
          delay(150);
          digitalWrite(ledPin,LOW);
        }
      digitalWrite(vishPin,HIGH);
      digitalWrite(ledPin,LOW);
      lcd.setCursor(0,0);
      lcd.print("**** ACCESS ****");
      lcd.setCursor(0,1);
      lcd.print("**** DENIED ****");
      delay(2000);
      lcd.setCursor(0,0);
      lcd.print(" Press # -> * to");
      lcd.setCursor(0,1);
      lcd.print("      retry     ");
   }  }

