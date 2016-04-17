
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "TickerAnimation.h"

const char* ssid = "Thing";
const char* password = "sparkfun";

ESP8266WebServer server(80);

const int PIN = 5;
const int NUMPIXELS = 64;
const int DELAY = 100;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN, 
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB + NEO_KHZ800);

//int x = 0;
//String text = "once upon a time, in a galaxy far, far away";
uint32_t textBackgroundColor;
uint32_t textColor;

TickerAnimation lovely(matrix);

void setup() {
  lovely.textColor = matrix.Color(40, 40, 40);
  lovely.textBackgroundColor = matrix.Color(0, 0, 0);
  lovely.textColor = matrix.Color(40, 0, 0);
//  textBackgroundColor = matrix.Color(10, 10, 10);
    
  matrix.begin();
  matrix.setTextColor(textColor);
  matrix.setTextWrap(false);

  server.on("/message", HTTP_GET, handleMessage);
  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() {
  server.handleClient();
  lovely.update(millis());
  delay(1);
}

void handleNotFound() {
  server.send(404, "text/plain", "nothing at this URI");
}
String page = "<! DOCTYPE html>\
<html>\
  <head>\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <style>\
      body { font-size: 200%; }\
      div { width: auto; padding: 1em 0; }\
      a { display: block; }\
      button { width: 100%; height: 10%; margin: 1em 0; font-size: 100%; font-weight: bold; }\
    </style>\
  </head>\
  <body>\
    <div>\
      <form action=\"/message\" method=\"get\">\
        <input type=\"text\" name=\"text\"/>\
        <select name=\"color\">\
          <option value=\"white\">White</option>\
          <option value=\"red\">Red</option>\
          <option value=\"green\">Green</option>\
          <option value=\"blue\">Blue</option>\
        </select>\
        <button id=\"submit\">Set Message</button>\
      </form>\
    </div>\
  </body>\
</html>";

void handleMessage() {
  String newText = server.arg("text");
  lovely.setText(newText);
  String newColor = server.arg("color");
  if (newColor.equals("white")) {
    lovely.setTextColor(matrix.Color(40, 40, 40));
  }
  if (newColor.equals("red")) {
    lovely.setTextColor(matrix.Color(120, 0, 0));
  }
  if (newColor.equals("blue")) {
      lovely.setTextColor(matrix.Color(0, 0, 120));
  }
  if (newColor.equals("green")) {
      lovely.setTextColor(matrix.Color(0, 120, 0));
  }
  server.send(200, "text/html", page);
}

void handleRoot() {
  server.send(200, "text/html", page);
}


