#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

  #define WIFI_SSID "Vyshnav"
  int val =0;
  const int IR =13; //D7 PIN
  int select=0;
  char ipaddress[255];
  char c[5]="n";
  IPAddress ClientIP(192,168,1,202);  //specify the ip of server here.....
  WiFiUDP UDP;

  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IR,INPUT);
  

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID);
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

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(IR) == HIGH){
    select = 1;
    Serial.println("1");
  }
  else
    {
      Serial.println("0");//object detected by ir
      select=0;
    }

  //sendind ip ipaddres append with LED to server
  if(select == 0)
    c[0]='y';
  else
    c[0]='n';
    
  int cb = UDP.parsePacket();
      {
        UDP.beginPacket(ClientIP, 3000);
        UDP.write(ipaddress); //Send ipaddress to server
        UDP.write("irs");
        UDP.write(c);
        UDP.endPacket();
        delay(1000);
      } 
}