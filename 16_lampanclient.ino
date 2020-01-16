// Lampan client (IP-adres eindigend op 182)
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include "LedControlMS.h"

#define BELSSID "HIERSSIDINVULLEN"
#define PASSWORD "WACHTWOORD"
#define IPADRES 182
#define BUZZER 3

#define MATRIX_DIN 5
#define MATRIX_CLK 4
#define MATRIX_CS 2

ESP8266WebServer BelWebserver(80);
LedControl lc=LedControl(MATRIX_DIN,MATRIX_CLK,MATRIX_CS, 1);

void setup() { 		
	pinMode(BUZZER,OUTPUT);
	Serial.begin(115200);	
	lc.shutdown(0,false); 
 lc.setIntensity(0,14);
 lc.clearDisplay(0);
 Aan();
 delay(500);
 Uit();
  
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

void Uit() {
 lc.clearDisplay(0);
 digitalWrite(BUZZER,LOW);
}

void Aan() {
	for(int i=0; i<8; i++)
	 for(int j=0; j<8; j++)
   lc.setLed(0,i,j,true);
}

void handleRoot() {
	BelWebserver.send(200, "text/html", "Bel MovieCave");
}

void handleBel() {	
	BelWebserver.send(200, "text/plain", "BEL");	
	for(int i=0; i<12; i++) {
		Aan();
		if(i<3) digitalWrite(BUZZER,HIGH);
		delay(500);
		Uit();
		delay(500);
	}
}
