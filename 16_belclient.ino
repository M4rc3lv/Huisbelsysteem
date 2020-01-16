// Bel-client (Slaapkamer Daan, IP-adres eindigend op 181)
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Servo.h>

#define SERVO 0
#define IPADRES 181
#define BELSSID "DraadloosnetwerkISSD"
#define PASSWORD "DraadloosnetwerkWachtwoord"

ESP8266WebServer BelWebserver(80);
Servo BelServo;

void setup() { 
	BelServo.attach(SERVO);
	Serial.begin(115200);	
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
 BelServo.write(0);
}

long t=millis();
void loop() {
 BelWebserver.handleClient();

 if(abs(millis()-t>5000)) {
 	t=millis();
 	BelServo.write(0);
 } 
}

void handleRoot() {
	BelWebserver.send(200, "text/html", "Belsysteem - (C) 2016");
}

void handleBel() {	
	BelWebserver.send(200, "text/plain", "BEL");
	
	for(int i=0; i<8; i++) {
		BelServo.write(179); 	
		delay(160);
	 BelServo.write(0);
	 delay(200);	
	}
}
