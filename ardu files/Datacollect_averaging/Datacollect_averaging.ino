#include <Wire.h>  
float vlt;
 unsigned char read_value[6];
char sign_temp=0;
char sign_volt=0;
char sign_current=0;
unsigned char m=1;
int d[4][32];
//int e[32][32];
int average(char,int);
signed long int avg;
 int tmp;
int curr;
int volt;
unsigned char i,j,k,n;
signed long int temp;
unsigned int a,b,c;
union RD_values
{
  uint16_t total_vlu;
  unsigned char rd_vlu[2]; 
}Total_read_value;

void setup() {
  Serial.begin(9600);
  Wire.begin();     // create a wire object
}
 
void loop() {
            while(1)
            {
    int c1 = read_values();  
   Serial.print("temp : ");
    
  
  Serial.println(read_value[1],HEX);
   Serial.println(read_value[0],HEX);
   Total_read_value.rd_vlu[0] = read_value[1];
   Total_read_value.rd_vlu[1] = read_value[0];
   //if()
   sign_temp = read_value[0] >> 7;
    a=(Total_read_value.total_vlu&0x7fff)>>5;
   Serial.print("a value");
  Serial.print(a);
 tmp=average(0,a);//function call for average calculation
 Serial.print("avg tmp value");
Serial.println(tmp);
  Serial.print("vtg: ");
 // int c2 = read_vtg();  
 
  Serial.println(read_value[3],HEX);
  Serial.println(read_value[2],HEX);
 
  Total_read_value.rd_vlu[0] = read_value[3];
   Total_read_value.rd_vlu[1] = read_value[2];
   sign_volt = read_value[2] >> 7;
  b=(Total_read_value.total_vlu&0x7fff)>>5;
  //while(1);
  Serial.print("b value");
  Serial.print(b);
  volt=average(1,b);//function call for average calculation
  vlt=volt*3.22; //multiplied by 3.22mV
  Serial.print("avg volt value");
Serial.println(vlt);
  Serial.print("current: ");
 // int c3 = read_current();  
   Serial.println(read_value[5],HEX);
   Serial.println(read_value[4],HEX);
   Total_read_value.rd_vlu[0] = read_value[5];
   Total_read_value.rd_vlu[1] = read_value[4];
   sign_current = read_value[4] >> 7;
  c=Total_read_value.total_vlu&0x7fff;
  Serial.print("c value");
  Serial.print(c);
   curr=average(2,c);//function call for average calculation
   Serial.print(" avg Curr value");
  Serial.println(curr);
 m=0; 
   delay(440);
}
}
 
int read_values() {
  
  unsigned int count;
  unsigned int c=0;
  //start the communication with IC with the address xx
  Wire.beginTransmission(0x48); 
  //send a bit and ask for register zero
  Wire.write(0x0A);
  //end transmission
  Wire.endTransmission();
  //request 1 byte from address xx
  Wire.requestFrom(0x48,6);
  //wait for response
  for(count=0; count<6;)
  {
    while(Wire.available() == 0);
    read_value[count] = Wire.read();
   
    count++;
    c = count;   
  }
  return c;
}
int average(char x,int y)
{
  if(m==1)//first time reading for sensor 
  {
    for(i=0;i<32;i++)
    {
      d[x][i]=y; //storing 1 value to 32 array positions
      Serial.println(d[x][i]);
     // delay(440);
      }
   //return d[--i][x];
  }
   
  else
  {
    temp=0;//second time entering
    Serial.print("new value");
    Serial.println(y);
    j=0;
    while(j<31)
    
    {
      //Serial.println(d[j][x]);
      d[x][j]=d[x][j+1];//moving the array position in  1 bit left
      Serial.println(d[x][j]);
     
      //delay(440);
      j+=1;
    }
    //Serial.print("3rd position");
    //Serial.print(d[2][x]);
  
    
   d[x][31]=y;//store the new data to last array position
   //Serial.print("next y value inserted last position");
    //Serial.println(d[x][5]);
for(k=0;k<32;k++)
{
  temp+=d[x][k];//add all values for averaging
}
Serial.print("added value");
Serial.print(temp);
avg=temp/32;//averaging process
//Serial.print("avg value");
//Serial.print(avg);
//return e[x][j-1];
return avg;//return average value
}
}

