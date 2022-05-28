#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID "Vyshnav"
#define WIFI_PASS "123454321"
#define UDP_PORT 1234

char receivedpack[255];
char sendon[20]="Alarm is on ";
char sendoff[20]="Alarm is off";

char lon[10]="on";
char loff[10]="off";

char ipaddress[255];


IPAddress ClientIP(192,168,43,141); //change ip



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


  IPAddress ip = WiFi.localIP();
        
  //ipaddress=WiFi.localIP().toString().c_str();
  sprintf(ipaddress, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

  UDP.begin(UDP_PORT);
  
}

void loop() {

  
  int cb = UDP.parsePacket();
      {
        UDP.beginPacket(ClientIP, 3000);
        UDP.write(ipaddress); //Send ipaddress to server
        UDP.write("ALARM");
      } 


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

     Serial.println("ALARM is ON");
     digitalWrite(D3, HIGH);
     Serial.println("success");
     

      
    // send back a reply, to the IP address and port we got the packet from
    UDP.beginPacket(ClientIP, 3000);
    UDP.write(sendon);
    UDP.endPacket();
    
    }


      
    else if(strcmp(receivedpack,loff)==0){
      Serial.println("ALARM is OFF");
      digitalWrite(D3, LOW);
      
      
    // send back a reply, to the IP address and port we got the packet from
    UDP.beginPacket(ClientIP, 3000);
    UDP.write(sendoff);
    UDP.endPacket();
      }
    
  }

}
