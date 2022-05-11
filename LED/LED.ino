#include <ESP8266WiFi.h>

const char* ssid ="Anol";
const char* password = "10009000";
//const char* ssid ="Vyshnav";
//const char* password = "12344321";
//const char* ssid ="Wi Fi Hi";
//const char* password = "qwertyuio";

WiFiServer server(80);

IPAddress staticIP(192,168,244,49);
//IPAddress gateway(192,168,244,208);
IPAddress subnet(255,255,255,0);
IPAddress dns(8,8,8,8);


void setup() {
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  WiFi.disconnect();
  WiFi.config(staticIP,subnet,WiFi.gatewayIP(),dns);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("NodeMCU is connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  server.begin();
  delay(3000);
}

void loop() {
  WiFiClient client;
  client = server.available();

 if (client == 1) {
    String request = client.readStringUntil('\n');
    client.flush();
    Serial.println(request);
    if (request.indexOf("ledon") != -1)
    { digitalWrite(D2, HIGH);
      Serial.println("LED is ON");
    }

    if (request.indexOf("ledoff") != -1)
    { digitalWrite(D2, LOW);
      Serial.println("LED is OFF");
    }
 
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); 
  
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title> Controlling LED </title>");
    client.println("</head>");
    client.println("<body align= \"center\" >");
    client.println("<h1> <font size = \"25\" face = \"Cooper\" >  NodeMCU and Wifi Network  </font> </h1> ");
    client.println("<p> <a href=\"/ledon\">  <button style=\"height:60px; background-color: yellow; width:200px; cursor: pointer\"> ON  </button> <a> </font></p> ");
    client.println("<p> <a href=\"/ledoff\"> <button style=\"height:60px; background-color: yellow; width:200px; cursor: pointer\" > OFF </button> <a> </font></p> ");
    client.println("</body>");
    client.println("</html>");

    Serial.println("Client disonnected");
    Serial.println("------------------");
    Serial.println("                  ");
       
  }
}
