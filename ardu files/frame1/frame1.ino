 char d=10;
 
byte ch[5] ={'0x02','0x01','0x00','0x03'};
void setup()
{
  Serial.begin(9600);
}
void loop()
{
 for(int i=0;i<4;i++)
   {
   Serial.println(ch[i]);
    delay(500);
}
}
