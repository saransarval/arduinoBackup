int aPin = 0; // A
int bPin = 1; // ________
int cPin = 2; // | |
int dPin = 3; // F | | B
int ePin = 4; // | G |
int fPin = 5; // |________|
int gPin = 6; ///
int num; // D
int dig1 = A0;
int dig2 = A1;
int dig3 = A2;
int dig4 = A3;
void setup()
{
pinMode(aPin, OUTPUT);
pinMode(bPin, OUTPUT);
pinMode(cPin, OUTPUT);
pinMode(dPin, OUTPUT);
pinMode(ePin, OUTPUT);
pinMode(fPin, OUTPUT);
pinMode(gPin, OUTPUT);
pinMode(A0, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(A3, OUTPUT);
}
void loop()
{


for(int i=0;i<10;i++)
{
  digitalWrite(A0,HIGH);
switch(i)
{
case 0: zero(); break;

case 1: one(); break;
case 2: two(); break;
case 3: three(); break;
case 4: four(); break;
case 5: five(); break;
case 6: six(); break;
case 7: seven(); break;
case 8: eight(); break;
default: nine(); break;
}
}
}
void clearLEDs()
{
digitalWrite( 2, LOW); // A
digitalWrite( 3, LOW); // B
digitalWrite( 4, LOW); // C
digitalWrite( 5, LOW); // D
digitalWrite( 6, LOW); // E
digitalWrite( 7, LOW); // F
digitalWrite( 8, LOW); // G
delay(1000);
}

void one()
{
digitalWrite( aPin, LOW);
digitalWrite( bPin, HIGH);
digitalWrite( cPin, HIGH);
digitalWrite( dPin, LOW);
digitalWrite( ePin, LOW);
digitalWrite( fPin, LOW);
digitalWrite( gPin, LOW);
delay(1000);
}
void two()
{
digitalWrite( aPin, HIGH);
digitalWrite( bPin, HIGH);
digitalWrite( cPin, LOW);
digitalWrite( dPin, HIGH);
digitalWrite( ePin, HIGH);
digitalWrite( fPin, LOW);
digitalWrite( gPin, HIGH);
delay(1000);
}
void three()
{
digitalWrite( aPin, HIGH);
digitalWrite( bPin, HIGH);
digitalWrite( cPin, HIGH);
digitalWrite( dPin, HIGH);
digitalWrite( ePin, LOW);
digitalWrite( fPin, LOW);
digitalWrite( gPin, HIGH);
delay(1000);
}
void four()
{
digitalWrite( aPin, LOW);
digitalWrite( bPin, HIGH);
digitalWrite( cPin, HIGH);
digitalWrite( dPin, LOW);
digitalWrite( ePin, LOW);
digitalWrite( fPin, HIGH);
digitalWrite( gPin, HIGH);
delay(1000);
}
void five()
{
digitalWrite( aPin, HIGH);
digitalWrite( bPin, LOW);
digitalWrite( cPin, HIGH);
digitalWrite( dPin, HIGH);
digitalWrite( ePin, LOW);
digitalWrite( fPin, HIGH);
digitalWrite( gPin, HIGH);
delay(1000);
}
void six()
{
digitalWrite( aPin, HIGH);
digitalWrite( bPin, LOW);
digitalWrite( cPin, HIGH);
digitalWrite( dPin, HIGH);
digitalWrite( ePin, HIGH);
digitalWrite( fPin, HIGH);
digitalWrite( gPin, HIGH);
delay(1000);
}
void seven()
{
digitalWrite( aPin, HIGH);
digitalWrite( bPin, HIGH);
digitalWrite( cPin, HIGH);
digitalWrite( dPin, LOW);
digitalWrite( ePin, LOW);

digitalWrite( fPin, LOW);
digitalWrite( gPin, LOW);
delay(1000);
}
void eight()
{
digitalWrite( aPin, HIGH);
digitalWrite( bPin, HIGH);
digitalWrite( cPin, HIGH);
digitalWrite( dPin, HIGH);
digitalWrite( ePin, HIGH);
digitalWrite( fPin, HIGH);
digitalWrite( gPin, HIGH);
delay(1000);
}
void nine()
{
digitalWrite( aPin, HIGH);
digitalWrite( bPin, HIGH);
digitalWrite( cPin, HIGH);
digitalWrite( dPin, HIGH);
digitalWrite( ePin, LOW);
digitalWrite( fPin, HIGH);
digitalWrite( gPin, HIGH);
delay(1000);
}
void zero()
{
digitalWrite( aPin, HIGH);
digitalWrite( bPin, HIGH);
digitalWrite( cPin, HIGH);
digitalWrite( dPin, HIGH);
digitalWrite( ePin, HIGH);
digitalWrite( fPin, HIGH);
digitalWrite( gPin, LOW);
delay(1000);
}
