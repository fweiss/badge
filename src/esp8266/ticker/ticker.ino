
#include "config.h"

#define WEBCONTROLLER

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifdef WEBCONTROLLER
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#endif

#include "TickerAnimation.h"
#include "StackAnimation.h"
#include "PlasmaAnimation.h"
#include "PixelAnimation.h"
#include "UberAnimation.h"

#include "WebPage.h"

const char* ssid = "Thing";
const char* password = "sparkfun";

#ifdef WEBCONTROLLER
ESP8266WebServer server(80);
#endif

const int PIN = 5;
const int NUMPIXELS = 64;
const int DELAY = 100;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN, 
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB + NEO_KHZ400);

uint32_t textBackgroundColor;
uint32_t textColor;

TickerAnimation ticker(matrix);
StackAnimation stack(matrix);
PlasmaAnimation plasma(matrix);
PixelAnimation pixel(matrix);
UberAnimation uberAnimation(25000);

void setup() {
  ticker.setText("Once upon a time, in a galaxy far, far away");
  ticker.textBackgroundColor = matrix.Color(0, 0, 0);
  ticker.textColor = matrix.Color(0, 60, 0);

  // until we get sequencer, manually start just one animation
  ticker.start();
//  plasma.start();
//  stack.start();

  uberAnimation.add(&ticker, &plasma, &pixel);
  uberAnimation.setCurrent(&pixel);
    
  matrix.begin();
  matrix.setTextColor(textColor);
  matrix.setTextWrap(false);

#ifdef WEBCONTROLLER
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(wifi_ssid, wifi_pass);
//  while ( WiFi.status() != WL_CONNECTED ) {
//    delay ( 500 );
//  }

  server.on("/message", HTTP_GET, handleMessage);
  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
#endif

}

void loop() {
  #ifdef WEBCONTROLLER
  server.handleClient();
  #endif

  uberAnimation.update(millis());
  
//  ticker.update(millis());
//  stack.update(millis());
//  plasma.update(millis());

//  matrix.show();
  
  delay(1);
}

#ifdef WEBCONTROLLER
void handleNotFound() {
  server.send(404, "text/plain", "nothing at this URI");
}

void handleMessage() {
  String newText = server.arg("text");
  ticker.setText(newText);
  String newColor = server.arg("color");
  if (newColor.equals("white")) {
    ticker.setTextColor(matrix.Color(40, 40, 40));
  }
  if (newColor.equals("red")) {
    ticker.setTextColor(matrix.Color(120, 0, 0));
  }
  if (newColor.equals("blue")) {
      ticker.setTextColor(matrix.Color(0, 0, 120));
  }
  if (newColor.equals("green")) {
      ticker.setTextColor(matrix.Color(0, 120, 0));
  }
  String tickerCheck = server.arg("ticker");
  if (tickerCheck.equals("on")) {
    uberAnimation.setCurrent(&ticker);
  }
  server.send(200, "text/html", page);
}

void handleRoot() {
  server.send(200, "text/html", page);
}
#endif



