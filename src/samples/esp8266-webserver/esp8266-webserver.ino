#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void setup() {
  server.on("/", HTTP_GET, handleRequest);
  server.onNotFound(handleRequest);
  server.begin(); 
}

void loop() {
  server.handleClient();
}

void handleRequest() {
  server.send(200, "text/plain", "hello");
}

