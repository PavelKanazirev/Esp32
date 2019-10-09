// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "XYZ";
const char* password = "ZYX";

// Set web server port number to 80
WiFiServer server(80);

void init_WebServer()
{  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

WiFiClient getWebClient()
{
  return server.available();   // Listen for incoming clients
}
