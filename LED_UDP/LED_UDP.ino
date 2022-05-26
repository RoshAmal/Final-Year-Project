#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID "Vyshnav"
#define WIFI_PASS "123454321"
#define UDP_PORT 1234 //udp port of nodemcu ....while sending from server give this port 1234

char receivedpack[255];
char sendon[]="led is on ";
char sendoff[]="led is off";

char lon[]="ledon";
char loff[]="ledoff";


IPAddress ClientIP(192,168,43,141);  //specify the ip of server here.....

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
  char led[]="LED/";
        
  //ipaddress=WiFi.localIP().toString().c_str();
  sprintf(ipaddress, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  strcat(LED,ipaddress);//append "LED" to ippaddress

  UDP.begin(UDP_PORT);
  
  //sendind ip ipaddres append with LED to server
  int cb = udp.parsePacket();
      {
        udp.beginPacket(ClientIP, 3000);
        udp.write(LED); //Send ipaddress to server
      } 
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
    if(strcmp(receivedpack,lon)==0){ //checks if received string is "ledon"

     Serial.println("LED is ON");
     digitalWrite(D3, HIGH);    //turn on led
     

      
    // send back a reply server as acknowledgement message
    UDP.beginPacket(ClientIP, 3000);
    UDP.write(sendon);
    UDP.endPacket();
    
    }


      
    else if(strcmp(receivedpack,loff)==0){ //checks if te received string is "ledoff"
      Serial.println("LED is OFF");
      digitalWrite(D3, LOW);  //turn off led
      
      
    //send back reply to server
    UDP.beginPacket(ClientIP, 3000);
    UDP.write(sendoff);
    UDP.endPacket();
    }
    
  }

}