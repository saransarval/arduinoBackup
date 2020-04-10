char pack[4];
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

while(Serial.available()==0);
char ch=Serial.read();
if(ch==2)
{
  for(int i=0;i<4;i++)
  {
     pack[i]=Serial.read();
  }
  for(int j=0;j<4;j++)
  {
   Serial.print(pack[j]);
  }
}

//int val=Serial.parseInt();
//Serial.println(val);
//long sum=
}
