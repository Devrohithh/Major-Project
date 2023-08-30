#include <LiquidCrystal.h>
#include <stdio.h>
#include <string.h>

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);

#include <Wire.h>
#include "dht.h"
#define dht_apin 8
dht DHT;


#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BMP280 bme;




#define ANALOG_PIN A0 // Analog pin
#define RESISTANCE 10.0 // Resistance in thousands of ohms
#define PANEL_LENGTH 53.0 // Length of solar cell in mm
#define PANEL_WIDTH 37.0 // Width of solar cell in mm
volatile float Area;
volatile float Power;
volatile float Radiation;

float Area1=0.0;

float multiplier=10000.0;



float tempc=0,humc=0;
float atm_pressure=0;

int sti=0; 
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete



void get_irradiation()
{
 Area = ((PANEL_LENGTH * PANEL_WIDTH) / multiplier); // we are dividing by 10000 get the area in square meters
 //Serial.print("Area:");Serial.println(Area);
 //Area1 = ((PANEL_LENGTH * PANEL_WIDTH) / multiplier);
 //Serial.print("Area1:");Serial.println(Area1);
  
  delay(100);
 Power = ((pow(analogRead(ANALOG_PIN), 2)) / RESISTANCE) ; // Calculating power
 //Serial.print("Power:");Serial.println(Power);
  delay(100);
 
 Radiation = (Power / Area);
}
 
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

   
 if(!bme.begin(0x76)) 
   {
    lcd.clear();lcd.print("BME Error");
    //Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
   }
     
    lcd.clear();
    lcd.write("T:");  //2,0
    lcd.setCursor(8,0);
    lcd.print("H:"); //10,0
    lcd.setCursor(0,1);
    lcd.write("AP:");  //3,1
    lcd.setCursor(8,1);
    lcd.write("SI:");  //11,1
}


void loop()
{
     DHT.read11(dht_apin);

      tempc = DHT.temperature;
      humc  = DHT.humidity;

    lcd.setCursor(2,0);convertl(tempc);
    lcd.setCursor(10,0);convertl(humc);

    //atm_pressure = bmp.readPressure();
    //atm_pressure = 717.8;
    atm_pressure = bme.readPressure();
    lcd.setCursor(3,1);convertl(atm_pressure); 
    delay(100);

    get_irradiation();
    lcd.setCursor(11,1);convertl(Radiation);
    
     Serial.write('*');
     converts(tempc);
     converts(humc);
     converts(atm_pressure);
     converts(Radiation);
     Serial.write('#');
       
 delay(1000);
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
