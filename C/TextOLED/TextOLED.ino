#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library


#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D

MicroOLED oled(PIN_RESET, DC_JUMPER);  // I2C Example

int SCREEN_WIDTH = oled.getLCDWidth();
int SCREEN_HEIGHT = oled.getLCDHeight();


void setup()
{
  oled.begin();
  oled.clear(PAGE
  );
  //oled.display();  
  oled.setFontType(0);
}

void loop()
{
  oled.setCursor(0, 0); 
  oled.print(":DDD"); // Print a const string
  
  oled.setCursor(0, 7);
  oled.print(":OOO");
  //oled.print(analogRead(0));  // Print an integer
  //oled.print(42.07);  // Print a float
  oled.display(); // Draw to the screen

  delay(1000);
}


