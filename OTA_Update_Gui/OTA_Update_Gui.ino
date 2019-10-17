#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>

#include <Update.h>

//const char* host = "esp32";
const byte DNS_PORT = 53;

IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

WebServer server(80);

#include "WebPages.h"
//#include "Web_Server_coms.h"


String Data="";

int LED_Pin = 5;
//************************************ Battery  Variables*******************
float Battery_Voltage=0.1;
float Battery_Percent=0.1;

#define Batt_Full_Voltage 4.20
#define Batt_Flat_Voltage 3.10



void setup(void) {
   pinMode(LED_Pin, OUTPUT);
  Serial.begin(115200);
 delay(100);
   WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("DNSclient CaptivePortal example");

  // if DNSclient is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
 dnsServer.start(DNS_PORT, "*", apIP);

Server_Coms();

}

void loop(void) {
 server.handleClient();
 dnsServer.processNextRequest();
  


}
