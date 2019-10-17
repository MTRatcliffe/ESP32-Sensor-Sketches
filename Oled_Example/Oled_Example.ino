/*
 * Random Nerd Tutorials - Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 * 
 * The MIT License (MIT)
 * Copyright (c) 2016 by Daniel Eichhorn
 */

 //Connect oled siplay to D5 and D4 
 
// Include the correct display library
// For a connection via I2C using Wire include
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  20        /* Time ESP32 will go to sleep (in seconds) */
int i=0;

#define SDA_PIN 21
#define SCL_PIN 22


// Initialize the OLED display using Wire library
SSD1306  display(0x3c, SDA_PIN, SCL_PIN);

void setup(){
   Serial.begin(115200);
  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

}

void displayInfo(){
 
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.clear();
  display.drawString(0, 0, "Lines Disp 0-16"); 
  display.drawString(0, 16, "Lines Disp 16-32"); 
  display.drawString(0, 32, "Lines Disp 32-48"); 
  display.drawString(0, 48, "Lines Disp 48-64"); 
  display.display();
}
void displayInfo2(){
  display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");
    display.display();
}
void loop(){
  displayInfo();
  delay(4000);
   displayInfo2();
   delay(6000);
   TurnOff_OLEd();
Turn_Into_Inputs();
Serial.println("Going to sleep now");
  delay(100);
  esp_deep_sleep_start();
  Serial.println("This will never be printed");

   
}



void TurnOff_OLEd(){
 display.clear();
  display.display();
delay(10000);
display.displayOff();
delay(10000);
display.end();



}


void Turn_Into_Inputs(){
  pinMode(SDA_PIN,INPUT);
  pinMode(SCL_PIN,INPUT);
}

