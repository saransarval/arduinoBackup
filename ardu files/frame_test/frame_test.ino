
 //char ch[4]="tin";
 //start/data/checksum/stop/
char  checksum();
void setup()
{
    Serial.begin(9600);
    
 //int d=10;
}
void loop()
{ 
 char d=1;
   //ch[3]={2,2,0,3};
while(1)
{
  char ch[4] ={2,d,0,3};//frame initialisation
     
    int value=0;
   for(int j=0;j<2;j++)
     {
     value^=ch[j];//simple check sum (xor operation)
     }
  ch[2]=value;//put into data send function in protocol test

   for(int i=0;i<4;i++)
   {
     Serial.println(ch[i],HEX);//send a frame to the serial port
     delay(500);
  
   }
   d=d+1;
}
}
  

