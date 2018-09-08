/**
 * Thank you to:
 * https://github.com/Kreezy-KRosa/ESP32IntTempSensorSoftAP/blob/master/ESP32internalTemp/ESP32internalTemp.ino
 */
 
#include <WiFi.h>

const char* ssid = "MY_ESP32_WIFI"; 
const char* password = "password1"; // should be 8 characters or more 
String header;

WiFiServer server(80);

IPAddress staticIP(10,10,10,10);
IPAddress gateway(10,10,10,1);      // setting the broadcast IP to 10.10.10.10
IPAddress subnet(255,255,255,0);  

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(staticIP, gateway, subnet);
  Serial.println();
  Serial.print("IP Address:");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // read from sensor here
  
   WiFiClient client = server.available();
   
   while(!client.available()){  delay(1); }
   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println("");
   client.println("<!DOCTYPE HTML>");
   client.println("<html>");
   client.println("<head>");
   client.println("<h1 style=""color:#ff0000"">");
   client.println("ESP32 Temp:");
   client.println("</h1>");
   client.println("</head>");
   client.println("</html>");
   client.stop();                                  
}
