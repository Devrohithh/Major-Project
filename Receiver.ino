#include <LiquidCrystal.h>
#include <stdio.h>
#include <string.h>

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);


int sti=0; 
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

 
void setup()
{
    Serial.begin(1200);
    serialEvent();


//8.LIFI based parameters monitoring system for Space Appliactions
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("   LIFI Based");
    lcd.setCursor(0,1);
    lcd.print("   Parameters ");
    delay(2500);
    
    lcd.clear();
    lcd.print(" Monitoring Sys");
    lcd.setCursor(0,1);
    lcd.print("For Space Applic");
    delay(2500);
    
      lcd.clear();
    lcd.write("T:");  //2,0
    lcd.setCursor(8,0);
    lcd.print("H:"); //10,0
    lcd.setCursor(0,1);
    lcd.write("AP:");  //3,1
    lcd.setCursor(8,1);
    lcd.write("SI:");  //11,1

  serialEvent();
}

char gchr1,gchr2,gchr3,gchr4,gchr5;
char gchr6,gchr7,gchr8,gchr9,gchr10;
char gchr11,gchr12,gchr13,gchr14,gchr15;
char gchr16,gchr17,gchr18,gchr19,gchr20;

void loop()
{
   if(stringComplete)
     {
       gchr1 = inputString[2];
       gchr2 = inputString[3];
       gchr3 = inputString[4];
       gchr4 = inputString[5];
       gchr5 = inputString[6];
       
       gchr6 = inputString[7];
       gchr7 = inputString[8];
       gchr8 = inputString[9];
       gchr9 = inputString[10];
       gchr10 = inputString[11];

       gchr11 = inputString[12];
       gchr12 = inputString[13];
       gchr13 = inputString[14];
       gchr14 = inputString[15];
       gchr15 = inputString[16];
       
       gchr16 = inputString[17];
       gchr17 = inputString[18];
       gchr18 = inputString[19];
       gchr19 = inputString[20];
       gchr20 = inputString[21];
       
      lcd.setCursor(2,0);lcd.write(gchr1);lcd.write(gchr2);lcd.write(gchr3);lcd.write(gchr4);lcd.write(gchr5);      
      lcd.setCursor(10,0);lcd.write(gchr6);lcd.write(gchr7);lcd.write(gchr8);lcd.write(gchr9);lcd.write(gchr10);
      lcd.setCursor(3,1);lcd.write(gchr11);lcd.write(gchr12);lcd.write(gchr13);lcd.write(gchr14);lcd.write(gchr15);      
      lcd.setCursor(11,1);lcd.write(gchr16);lcd.write(gchr17);lcd.write(gchr18);lcd.write(gchr19);lcd.write(gchr20);
      
      inputString = "";
      stringComplete = false;              
     }
 delay(100);
}



void serialEvent() 
{
   while(Serial.available()) 
        {         
         char inChar = (char)Serial.read();
          if(inChar == '*')
            {sti=1;
              inputString += inChar;
            }
          if(sti == 1)
            {
                inputString += inChar;
            }
          if(inChar == '#')
            {sti=0;
              stringComplete = true;      
            }
        }
}



void converts(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   Serial.write(a);
   Serial.write(c);
   Serial.write(e); 
   Serial.write(g);
   Serial.write(h);
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   lcd.write(a);
   lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}
