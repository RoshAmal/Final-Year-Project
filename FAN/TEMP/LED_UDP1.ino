#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID "Anol"
#define WIFI_PASS "10009000"
#define UDP_PORT 1234

char receivedpack[255];
char sendon[20]="led is on ";
char sendoff[20]="led is off";

char lon[10]="ledon";
char loff[10]="ledoff";


IPAddress ClientIP(192,168,43,141);



WiFiUDP UDP;
  


void setup() {
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  Serial.begin(9600);
  Serial.print("Connecting  ");
  

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("NodeMCU is connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(3000);

  UDP.begin(UDP_PORT);
  
}
  
void loop() {

  
    
  int packetSize = UDP.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    int len = UDP.read(receivedpack, 255);
    if (len > 0)
    {
      receivedpack[len] = 0;
    }
    Serial.println(receivedpack);
    if(strcmp(receivedpack,lon)==0){

     Serial.println("LED is ON");
     digitalWrite(D3, HIGH);
     

      
    // send back a reply, to the IP address and port we got the packet from
    UDP.beginPacket(ClientIP, 57);
    UDP.write(sendon);
    UDP.endPacket();
    
    }


      
    else if(strcmp(receivedpack,loff)==0){
      Serial.println("LED is OFF");
      digitalWrite(D3, LOW);
      
      
    // send back a reply, to the IP address and port we got the packet from
    UDP.beginPacket(ClientIP, 57);
    UDP.write(sendoff);
    UDP.endPacket();
      }
    
  }

}