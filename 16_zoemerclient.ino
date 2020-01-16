// Zoemer (183)
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include "LedControlMS.h"

#define BELSSID "WifiISSD"
#define PASSWORD "WifiWachtwoord"
#define IPADRES 183
#define ZOEMER 0 // Zit met GND aan D0 en + aan Vin
#define DOT 80

// Zomer:
#define AAN HIGH
#define UIT LOW

ESP8266WebServer BelWebserver(80);

void setup() { 		
	pinMode(ZOEMER,OUTPUT);
	digitalWrite(ZOEMER,UIT);
	Serial.begin(115200);		
 delay(100);
   
	WiFi.config(IPAddress(192,168,0,IPADRES), IPAddress(192,168,0,1), IPAddress(255,255,255,0));
	WiFi.begin(BELSSID, PASSWORD);
	while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
 }
		
	BelWebserver.on("/", handleRoot);
	BelWebserver.on("/bel", handleBel);
	BelWebserver.begin();
	Serial.println("Webserver gestart");
	Serial.print("IP-adres: ");
 Serial.println(WiFi.localIP());  
}

long t=millis();
void loop() {
 BelWebserver.handleClient();
}

void handleRoot() {
	BelWebserver.send(200, "text/html", "Bel Zoemerclient");
}

void handleBel() {	
	BelWebserver.send(200, "text/plain", "BEL");	
	Zoem();
}

void Zoem() {
	for(int j=0; j<3; j++) {
  for(int i=0; i<3; i++) {
   digitalWrite(ZOEMER,AAN);
   delay(DOT);
   digitalWrite(ZOEMER,UIT);
   delay(DOT);
  }

  digitalWrite(ZOEMER,AAN);
  delay(((j+1)*3)*DOT);
  digitalWrite(ZOEMER,UIT);
  delay(DOT);

  digitalWrite(ZOEMER,AAN);
  delay(DOT);
  digitalWrite(ZOEMER,UIT);
  delay(DOT);

  delay(2*DOT);
 }
 delay(5*DOT);
}

