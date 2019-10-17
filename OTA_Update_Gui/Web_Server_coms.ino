/*
 * Routines For handaling the website side, what pages to send and what values to update etc
 * 
 * 
 * 
 * 
 * 
 */

void Server_Coms(){
  
server.begin();
//**************************************************** OTA Updates ***************************************************************
//********************************************************************************************************************************
//********************************************************************************************************************************
  server.on("/Update", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", OTA_HTML);
    });
    server.on("/update", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "Update Sucessfull");
      ESP.restart();
    }, []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        Serial.printf("Update: %s\n", upload.filename.c_str());
        if (!Update.begin()) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      }
    });



//**************************************************** Serve Index ***************************************************************
//********************************************************************************************************************************
//********************************************************************************************************************************

//User has typed www.example.com ****************** Serve them the index HTMl
   server.on("/", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", Index_HTML);
    });



//**************************************************** User Interaction **********************************************************
//********************************************************************************************************************************
//********************************************************************************************************************************  
     server.on("/Send_Sensor_Data_18650", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      Serial.println("User GUI Asked For Data");    
      Send_Server_Sensor_Data();
      //server.send(200, "text/html", "LED is ON");

      
      
      
    });

 
};



//**************************************************** User asked for info, lets deliver it **************************************
//********************************************************************************************************************************
//******************************************************************************************************************************** 
void Send_Server_Sensor_Data(){

Data ="{";

Read_Battery_Voltage();
Data += "\"""Battery_Voltage""\":""\""+String(Battery_Voltage)+"\",";
Data += "\"""Battery_Percent""\":""\""+String(Battery_Percent)+"\"";


Data +="}";



Serial.println("Sent Battery Data to Web page");
server.send(200, "application/json", Data);

}


