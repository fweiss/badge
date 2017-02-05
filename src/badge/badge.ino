
//#include "config.h"

// options for remote controller
// NOCONTROLLER - no remote
// WEBCONTROLLER - esp8266
// BTCONTROLLER - Feather BLE
#define BTCONTROLLER

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "SplashAnimation.h"
#include "TickerAnimation.h"
#include "StackAnimation.h"
#include "PlasmaAnimation.h"
#include "PixelAnimation.h"
#include "BitmapAnimation.h"
#include "FaceAnimation.h"
#include "AumAnimation.h"
#include "UberAnimation.h"

//const char* ssid = "Thing";
//const char* password = "sparkfun";

const int PIN = 5;
const int NUMPIXELS = 64;
//const int DELAY = 100;

// to accomodate packaging of the LED matrix with different locations of the connector
const int rotationZero = NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS;
const int rotationNinety = NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS;
const int rotationOneEighty = NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN, 
    rotationOneEighty + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ400);

SplashAnimation splash(matrix);
TickerAnimation ticker(matrix);
StackAnimation stack(matrix);
PlasmaAnimation plasma(matrix);
PixelAnimation pixel(matrix);
FaceAnimation face(matrix);
AumAnimation sacred(matrix);

const unsigned long controllerPeriod = 50000; //26000

#if defined WEBCONTROLLER
#include "WebController.h"
WebController uberAnimation(controllerPeriod);
#elif defined BTCONTROLLER
#include "BTController.h"
BTController uberAnimation(controllerPeriod);
#else // NOCONTROLLER
UberAnimation uberAnimation(controllerPeriod);
#endif

const String testCp437 = "\xC2\x80\xC2\x81\xC2\x82\xC2\x83\xC3\xBB";

void setup() {
//    ticker.setText("Once upon a time, in a galaxy far, far away");
    ticker.setText(testCp437);
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
    uberAnimation.setup();
}

void loop() {
    uberAnimation.update(millis());
    delay(1);
}

