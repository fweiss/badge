
//#include "config.h"

// options for remote controller
// NOCONTROLLER - no remote
// WEBCONTROLLER - esp8266
#define NOCONTROLLER

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
#include "BitmapAnimation.h"
#include "FaceAnimation.h"
#include "AumAnimation.h"
#include "UberAnimation.h"

#include "WebPage.h"

const char* ssid = "Thing";
const char* password = "sparkfun";

#include "WebController.h"

const int PIN = 5;
const int NUMPIXELS = 64;
const int DELAY = 100;

//Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN, 
//  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
//  NEO_GRB + NEO_KHZ400);
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN, 
  NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB + NEO_KHZ400);

TickerAnimation ticker(matrix);
StackAnimation stack(matrix);
PlasmaAnimation plasma(matrix);
PixelAnimation pixel(matrix);
FaceAnimation face(matrix);
AumAnimation sacred(matrix);
//UberAnimation uberAnimation(26000);
//UberAnimation uberAnimation(5000);
WebController uberAnimation(5000);


void setup() {
  ticker.setText("Once upon a time, in a galaxy far, far away");
  ticker.textBackgroundColor = matrix.Color(0, 0, 0);
  ticker.textColor = matrix.Color(0, 60, 0);

  // comment out any to skip on startup
  ticker.start();
  stack.start();
  plasma.start();
  pixel.start();
  face.start();
  sacred.start();
    
  matrix.begin();
}

void loop() {
  #ifdef WEBCONTROLLER
  server.handleClient();
  #endif

  uberAnimation.update(millis());

  delay(1);
}

