#include <ESP8266WiFi.h>
#include <DHT.h>
#include <WiFiUdp.h>
#include <Wire.h>

  
// Set WiFi credentials
const char *ssid = "Vyshnav";
const char *pass = "123454321";
unsigned int localPort = 3000; // local port to listen for UDP packets


IPAddress ClientIP(192,168,237,253);
      
#define DHTPIN 0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float t = 0.0;
float h = 0.0;
char ipaddress[255];
char packetBuffer[255];
char replyBuffer[255] = "Hi there ";
char macaddress[255];

WiFiUDP udp;
  
void setup() {
  Serial.begin(115200);
  Serial.println();

  dht.begin();

  pinMode(D2 ,OUTPUT);
  
  // Begin WiFi
  WiFi.begin(ssid, pass);
  
  
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  // Connected to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(WiFi.localIP());
  IPAddress ip = WiFi.localIP();
 
        
  //ipaddress=WiFi.localIP().toString().c_str();
  sprintf(ipaddress, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  
}
 
void loop() {

  float newT = dht.readTemperature();
    //Read temperature as Fahrenheit (isFahrenheit = true)
   
    if (isnan(newT))
    {
      Serial.println("Failed to read from DHT sensor!");
    }
    else
    {
      t = newT;
      Serial.println(t);
    }
    // Read Humidity
    float newH = dht.readHumidity();
   
    if (isnan(newH))
    {
      Serial.println("Failed to read from DHT sensor!");
    }
    else
   {
      h = newH;
      Serial.println(h);
    }
    
    char temp[20];
    char hum[20];

    //function to convert to string
    
   sprintf(temp, "%f", t);//make the number into string using sprintf function
   sprintf(hum, "%f", h);
      
     int cb = udp.parsePacket();
      {
        udp.beginPacket(ClientIP, 3000);
        udp.write(ipaddress); //Send one byte to ESP8266
        udp.write(temp);
        udp.write(hum);
        udp.endPacket();
        delay(10000);
      } 
 
}