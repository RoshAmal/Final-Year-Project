#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>


//const char* ssid ="Anol";
//const char* password = "10009000";
const char* ssid ="Vyshnav";

unsigned int localPort = 3000; // local port to listen for UDP packets
int val=0;
char cnt[10]="";
WiFiUDP udp;
IPAddress ClientIP(192,168,1,202); //to change



void setup() {
  Serial.begin(9600); // sensor buart rate  
  pinMode(14,HIGH);  // Led Pin Connected To D5 Pin  

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);


  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {


  cnt[0]='N';
  val = digitalRead(5); // IR Sensor output pin connected to D1  
  Serial.println(val);  // see the value in serial m0nitor in Arduino IDE  
  delay(100);      // for timer  
  if(val == 1 )  
  {
  
    //send by udp to server
    cnt[0]='Y';
  
  }  

  int cb = udp.parsePacket();
      {
        udp.beginPacket(ClientIP, 3000);
        udp.write(val); //Send one byte to ESP8266
        udp.write("IRS");
        udp.endPacket();
        delay(1000);
      } 
}
