#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>

const char WiFiAPPSK[] = "sparkfun";

#define PIN 5
#define NUMPIXELS 64
#define PIXELS_PER_CHAR 6
#define DELAY 100

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN, 
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB + NEO_KHZ800);

int x = 0;
String text = "once upon a time, in a land far, far away";

WiFiServer server(80);

void setup() {
  matrix.begin();
  matrix.setTextColor(matrix.Color(40, 40, 40));
  matrix.setTextWrap(false);

  setupWifiAccessPoint();
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    handleClient(client);
  }
  
  matrix.fillScreen(0);
  matrix.setCursor(-x, 0);
  matrix.print(text);
  matrix.show();
  x = (x + 1) % (text.length() * PIXELS_PER_CHAR);
  delay(DELAY);
}

void setupWifiAccessPoint()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "Badge " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}

void handleClient(WiFiClient &client) {
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  client.flush();

  if (req.indexOf("/submit") != -1) {
    int p1 = req.indexOf("?text=");
    int p2 = req.lastIndexOf(" ");
    if (p1 > -1 && p2 > -1) {
      p1 += 6;
      if (p1 < p2) {
          String newText = req.substring(p1, p2);
          urlDecode(newText);
          text = newText;
      }
    }
  }
  client.flush();

  // Prepare the response. Start with the common header:
  String style =
    "body { font-size: 200%; }"
    "div { width: auto; padding: 1em 0; }"
    "a { display: block; }"
    "button { width: 100%; height: 10%; margin: 1em 0; font-size: 100%; font-weight: bold; }";

  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  s += "<style>" + style + "</style>";
  s += "</head>";
  s += "<body>";

  s += "<form method=\"get\" action=\"submit\"><input type=\"text\" name=\"text\"/><input type=\"submit\"/></form>";
  
  s += "</body></html>\n";

  // Send the response to the client
  client.print(s);
}

void urlDecode(String &param) {
  param.replace("+"," ");
  param.replace("%21","!");
  param.replace("%23","#");
  param.replace("%24","$");
  param.replace("%26","&");
  param.replace("%27","'");
  param.replace("%28","(");
  param.replace("%29",")");
  param.replace("%2A","*");
  param.replace("%2B","+");
  param.replace("%2C",",");
  param.replace("%2F","/");
  param.replace("%3A",":");
  param.replace("%3B",";");
  param.replace("%3D","=");
  param.replace("%3F","?");
  param.replace("%40","@");
  param.replace("%5B","[");
  param.replace("%5D","]");
}

