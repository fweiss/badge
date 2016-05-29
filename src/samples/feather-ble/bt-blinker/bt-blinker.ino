#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
  #include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"
// CS 8
// IRQ 7
// RST 4

static const int PIN = 13;

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

void setup() {
  pinMode(PIN, OUTPUT);
  boolean debug = false;
  ble.begin(debug);
  ble.echo(false);
  while (!ble.isConnected()) {
    delay(500);
  }
  ble.setMode(BLUEFRUIT_MODE_DATA);
  digitalWrite(PIN, LOW);
}

// note that Bluefruit LE client adds NL when SEND button is pressed
void loop() {
  if (ble.available()) {
    int c = ble.read();
    if (c != -1 && c != 0x0A) {
      digitalWrite(PIN, (char)c == 'a' ? HIGH : LOW);
    }
  }
}

