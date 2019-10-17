/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10        /* Time ESP32 will go to sleep (in seconds) */
int i=0;

#define SDA_PIN 21
#define SCL_PIN 22
#define BME280_ADDRESS (0x76)
#define BME_Adrr 0x76


#include <Wire.h>
//#include <SPI.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

bool BME_Status = 0;




void setup() {
  Serial.begin(115200);
  Wire.setClock(10000) ;
   pinMode(23,OUTPUT);
   digitalWrite(23,LOW);

   /*
First we configure the wake up source
  We set our ESP32 to wake up every 5 seconds
  */
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");





  pinMode(SDA,INPUT_PULLUP);
pinMode(SCL,INPUT_PULLUP);
  //Wire.pins(SDA_PIN, SCL_PIN);// yes, see text

   digitalWrite(23,HIGH);
  Wire.begin(SDA_PIN, SCL_PIN); // 0=sda, 2=scl
 // i2c.setup(0, sda, scl, i2c.SLOW)//-- call i2c.setup() only once
//Wire.setClockStretchLimit(1500); 
  Serial.println(F("BME280 test"));
  delay(100);
 // Wire.setClock(10000);
  Setup_BME();

}


void loop() {
  Read_BME();
  delay(1000);
  if(i>20){
    Turn_Into_Inputs();

  Serial.println("Going to sleep now");
  delay(100);
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
  } 
  i++;
}


void Read_BME() {
//BME_Status = 1;

  BME_Status = bme.begin(BME_Adrr);
 //bme.takeForcedMeasurement();
 delay(10);
  if (BME_Status == 1) {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
delay(100);
    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
  }
  else Serial.println("BME Error");
  // bme.writeMode(smSleep);
}


void Setup_BME() {


  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  BME_Status = bme.begin(BME_Adrr);
  delay(100);
  if (!BME_Status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    delay(100);
  }

  else Serial.println("-- BME Error --");


  Serial.println();
/*
 Serial.println("-- Weather Station Scenario --");
    Serial.println("forced mode, 1x temperature / 1x humidity / 1x pressure oversampling,");
    Serial.println("filter off");
    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF   );
*/
}




void Turn_Into_Inputs(){
  pinMode(SDA_PIN,INPUT);
  pinMode(SCL_PIN,INPUT);
   pinMode(23,INPUT);
}

