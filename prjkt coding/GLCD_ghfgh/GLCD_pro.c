#include <16F877A.h>
#use delay(clock=11059200)
#include "Header_GLCD.h"

#FUSES NOWDT, HS

#byte trisb=0x86
#byte portb=0x06

#byte trisc=0x87
#byte portc=0x07

#byte trisd=0x88
#byte portd=0x08

#byte trise=0x89
#byte porte=0x09

void display_image(void);

char PAGE1_TOP[]="STAFF INFO";
char PAGE1_BOTTOM[]="APP CTRL";

char PAGE2_ECE[]="ECE";
char PAGE2_EEE[]="EEE";
char PAGE2_CSC[]="CSC";
char PAGE2_MEK[]="MEK";

char PAGE2A_N1_ECE[]="RAM";
char PAGE2A_N2_ECE[]="SAM";
char PAGE2A_N3_ECE[]="MAM";
char PAGE2A_N4_ECE[]="HAM";

char PAGE2B_N1_EEE[]="RAM1";
char PAGE2B_N2_EEE[]="SAM1";
char PAGE2B_N3_EEE[]="MAM1";
char PAGE2B_N4_EEE[]="HAM1";

void page1(void);
void page2(void);
void page2A(void);
void pagE2B(void);

const int image1[128]={0x00,0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0xFC,0xFC,0xFC,
0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0xFC,0xFC,0xFC,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x7C,0x7C,0x7C,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,
0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0xF0,0xF0,0xF0,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,
0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,
0x70,0x70,0x70,0x70,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00};


const int image2[128]={0x00,0x00,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00};


const int image3[128]={0x00,0x00,0xFF,0xFF,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF,0xFF,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00};


const int image4[128]={0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x00,0x00,
0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00};


const int image5[128]={0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,
0x70,0x70,0x70,0x70,0x70,0x70,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0x70,0x70,0x70,0x70,
0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,
0x70,0x70,0x70,0x70,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00};


const int image6[128]={0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00};


const int image7[128]={0x00,0x00,0x00,0x00,0xF8,0xF8,0xF8,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00};


const int image8[128]={0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x1F,0x1F,0x1F,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1F,0x0F,0x0F,0x0E,0x0E,0x0E,0x0E,
0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,
0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00};



void main()
{

   glcd_init(ON);
   delay_ms(1000);

   display_image();
   delay_ms(3000);

   //glcd_fillScreen(NO);

      while(1);
      {
         page1();
         delay_ms(2000);
         glcd_fillScreen(NO);

         page2();
         delay_ms(2000);
         glcd_fillScreen(NO);

         page2A();
         delay_ms(2000);
         glcd_fillScreen(NO);

         page2B();
         delay_ms(2000);
         glcd_fillScreen(NO);

        /* glcd_line(32, 26, 96, 26, ON);
         glcd_line(96, 26, 96, 38, ON);
         glcd_line(32, 38, 96, 38, ON);
          glcd_line(32, 26, 32, 38, ON);
         //glcd_RECT(32,26,96,34,1,OFF);
         //glcd_pixel(1,1,ON);*/

      }
}

void page1(void)
{
   glcd_text57(10, 10, PAGE1_TOP, 2, ON); DELAY_MS(100);
   glcd_text57(10, 44, PAGE1_BOTTOM, 2, ON); DELAY_MS(100);
}

void page2(void)
{
  glcd_text57(10, 10, PAGE2_ECE, 2, ON); DELAY_MS(100);
  glcd_text57(80, 10, PAGE2_EEE, 2, ON); DELAY_MS(100);

   glcd_text57(10, 40, PAGE2_CSC, 2, ON); DELAY_MS(100);
   glcd_text57(80, 40, PAGE2_MEK, 2, ON); DELAY_MS(100);
}

void page2A(void)
{
  glcd_text57(10, 10, PAGE2A_N1_ECE, 2, ON); DELAY_MS(100);
  glcd_text57(80, 10, PAGE2A_N2_ECE, 2, ON); DELAY_MS(100);

   glcd_text57(10, 40, PAGE2A_N3_ECE, 2, ON); DELAY_MS(100);
   glcd_text57(80, 40, PAGE2A_N4_ECE, 2, ON); DELAY_MS(100);
}

void page2B(void)
{
  glcd_text57(10, 10, PAGE2B_N1_EEE, 2, ON); DELAY_MS(100);
  glcd_text57(80, 10, PAGE2B_N2_EEE, 2, ON); DELAY_MS(100);

   glcd_text57(10, 40, PAGE2B_N3_EEE, 2, ON); DELAY_MS(100);
   glcd_text57(80, 40, PAGE2B_N4_EEE, 2, ON); DELAY_MS(100);
}

void display_image(void)
{
   unsigned char count, for_var;

   for(for_var=0; for_var<8; for_var++)
   {
      output_low(GLCD_DI);
      glcd_writeByte(GLCD_CS1, (0xB8+for_var));
      glcd_writeByte(GLCD_CS2, (0xB8+for_var));
      glcd_writeByte(GLCD_CS1, 0xC0);
      glcd_writeByte(GLCD_CS2, 0xC0);
      output_high(GLCD_DI);

      for(count=0; count<64; count++)
      {
         switch(for_var)
         {
            case 0:  glcd_writeByte(GLCD_CS1, image1[count]);
            break;

            case 1:  glcd_writeByte(GLCD_CS1, image2[count]);
            break;

            case 2:  glcd_writeByte(GLCD_CS1, image3[count]);
            break;

            case 3:  glcd_writeByte(GLCD_CS1, image4[count]);
            break;

            case 4:  glcd_writeByte(GLCD_CS1, image5[count]);
            break;

            case 5:  glcd_writeByte(GLCD_CS1, image6[count]);
            break;

            case 6:  glcd_writeByte(GLCD_CS1, image7[count]);
            break;

            case 7:  glcd_writeByte(GLCD_CS1, image8[count]);
            break;


         }
      }

      for(count=0; count<64; count++)
      {
         switch(for_var)
         {
            case 0:  glcd_writeByte(GLCD_CS2, image1[count+64]);
            break;

            case 1:  glcd_writeByte(GLCD_CS2, image2[count+64]);
            break;

            case 2:  glcd_writeByte(GLCD_CS2, image3[count+64]);
            break;

            case 3:  glcd_writeByte(GLCD_CS2, image4[count+64]);
            break;

            case 4:  glcd_writeByte(GLCD_CS2, image5[count+64]);
            break;

            case 5:  glcd_writeByte(GLCD_CS2, image6[count+64]);
            break;

            case 6:  glcd_writeByte(GLCD_CS2, image7[count+64]);
            break;

            case 7:  glcd_writeByte(GLCD_CS2, image8[count+64]);
            break;


         }
      }

   }
}

