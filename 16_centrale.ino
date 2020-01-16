#include <ESP8266WiFi.h>

#define BELSSID "ISSDNETWERK"
#define PASSWORD "WACHTWOORDJE"

#define BEL1 0
#define BEL2 2
#define BEL3 4
#define BEL4 5
#define GROEN  14
#define BLAUW  13

void setup() { 
	pinMode(BEL1,INPUT_PULLUP);
	pinMode(BEL2,INPUT_PULLUP);
	pinMode(BEL3,INPUT_PULLUP);
	pinMode(BEL4,INPUT_PULLUP);
	pinMode(GROEN,OUTPUT);
	pinMode(BLAUW,OUTPUT);
	
	digitalWrite(BLAUW,LOW);
	delay(200);
	digitalWrite(BLAUW,HIGH);
	
	Serial.begin(115200);	
	WiFi.config(IPAddress(192,168,0,180), IPAddress(192,168,0,1), IPAddress(255,255,255,0));
	WiFi.begin(BELSSID, PASSWORD);
	while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
 }

	digitalWrite(BLAUW,LOW);
	Serial.print("IP-adres: ");
 Serial.println(WiFi.localIP());
}

void loop() {
 boolean bel1=digitalRead(BEL1)==LOW;
 boolean bel2=digitalRead(BEL2)==LOW;
 boolean bel3=digitalRead(BEL3)==LOW;
 boolean bel4=digitalRead(BEL4)==LOW;

 if(bel1 || bel2 || bel3 || bel4) {
  Serial.print("Bel1-4: ");
  Serial.print(bel1);Serial.print(" ");
  Serial.print(bel2);Serial.print(" ");
  Serial.print(bel3);Serial.print(" ");
  Serial.println(bel4);
 }
  
 if(bel1) Bel(1);
 if(bel2) Bel(2);
 if(bel3) Bel(3);
 if(bel4) Bel(4);
 digitalWrite(BLAUW,LOW);
 digitalWrite(GROEN,LOW);
}

void Bel(int Nummer) {
	digitalWrite(BLAUW,HIGH);
	Serial.print("Bel ");Serial.println(Nummer);
 static const char * Host[]={"192.168.0.181","192.168.0.182",
  "192.168.0.183","192.168.0.184"
 };
 Serial.println(Nummer);  
 WiFiClient client; 
 if(!client.connect(Host[Nummer-1], 80)) {
  Serial.println("connection failed");
  return;
 }
  
 String url = "/bel";
 Serial.print("Requesting URL: ");
 Serial.println(url);
  
 client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + Host[Nummer-1] + "\r\n" + 
               "Connection: close\r\n\r\n");
 delay(10);
 while(client.available()){
 	digitalWrite(BLAUW,LOW);
 	digitalWrite(GROEN,HIGH);
  String line = client.readStringUntil('\r');
  
  Serial.print(line);
 }

 delay(220);
 digitalWrite(GROEN,HIGH);
 digitalWrite(BLAUW,HIGH);
}

