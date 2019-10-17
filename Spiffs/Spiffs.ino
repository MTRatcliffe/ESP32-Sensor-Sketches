#include "SPIFFS.h"
#include "FS.h"
const char* Header_data = "Time, Date, Humidity %, Air Pressure hPa, Air Temp *C, Water EC ms/cm, Water Temp *C, Battery Voltage";
String debugLogData="";
int i=0;
void setup() {
Serial.begin(115200);
SPIFFS.format();
//Mounting Spiffs
if (SPIFFS.begin(true)) {
Serial.println("Spiffs Mounted");
//checking if Spiffs has been used before    
if(!SPIFFS.exists("/datalog.csv")){
Serial.println("No File Found, must be new code/controller");
Serial.println("Please wait 30 secs for SPIFFS to be formatted");
SPIFFS.format();
Serial.println("Spiffs formatted");
//writing log header data
File Logfile = SPIFFS.open("/datalog.csv", FILE_WRITE);
Logfile.println(Header_data);
Logfile.close();
delay(10);
Logfile = SPIFFS.open("/datalog.csv");
while (Logfile.available()){
            debugLogData += char(Logfile.read());
          }
Serial.println("=====================================");
Serial.println(debugLogData);
Serial.println("=====================================");
Logfile.close();
                                    }
                          }
             
else Serial.println("Spiffs Failed to mount");
SPIFFS.end();             
}
 
void loop() {
  i++;
  Serial.println("Logging Data");
 if (SPIFFS.begin(true)) {
//writing log header data
File Logfile = SPIFFS.open("/datalog.csv", FILE_APPEND);
delay(10);
Logfile.println(String(i));
delay(100);
Logfile.close();

delay(10);
Logfile = SPIFFS.open("/datalog.csv");
debugLogData ="";
while (Logfile.available()){
debugLogData += char(Logfile.read());
}
Serial.println("=====================================");
Serial.println(debugLogData);
Serial.println(Logfile.size());
Serial.println("=====================================");                                  
Logfile.close();
}
else Serial.println("Spiffs Failed to mount");
SPIFFS.end();  
delay(1000);  
  
  }

