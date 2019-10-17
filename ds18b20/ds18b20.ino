// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 0
#define ONE_WIRE_Power 17
#define ONE_WIRE_Ground 4

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature DS18B20(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;


float Water_Temp=-99;
/*
 * Setup function. Here we do the basics
 */
void setup(void)
{
  pinMode(ONE_WIRE_Power,OUTPUT);
  digitalWrite(ONE_WIRE_Power,HIGH);
  
  pinMode(ONE_WIRE_Ground,OUTPUT);
  digitalWrite(ONE_WIRE_Ground,LOW);
 delay(10);
  // start serial port
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // locate devices on the bus
  Serial.print("Locating devices...");
  DS18B20.begin();
  Serial.print("Found ");
  Serial.print(DS18B20.getDeviceCount(), DEC);
  Serial.println(" devices.");

  
  if (!DS18B20.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  
  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
 /* Resolution  Increment Time
9 bit 0.5 degrees C 93.75 mSec
10 bit  0.25 degrees C  187.5 mSec
11 bit  0.125 degrees C 375 mSec
12 bit  0.0625 degrees C  750 mSec */
  DS18B20.setResolution(insideThermometer, 12);
 
  Serial.print("Device 0 Resolution: ");
  Serial.print(DS18B20.getResolution(insideThermometer), DEC); 
  Serial.println();
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
 
  // method 2 - faster
  float tempC = DS18B20.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
 
}
/*
 * Main function. It will request the tempC from the DS18B20 and display on Serial.
 */
void loop(void)
{ 
  //delay(200);
  // call DS18B20.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  DS18B20.requestTemperatures();
  Water_Temp=DS18B20.getTempCByIndex(0);
   Serial.println(Water_Temp);
  // It responds almost immediately. Let's print out the data
 // printTemperature(insideThermometer); // Use a simple function to print out the data
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
