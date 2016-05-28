#ifndef WEBCONTROLLER_H
#define WEBCONTROLLER_H

#include "UberAnimation.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class WebController : public UberAnimation {
private:
  static String page;
protected:
  ESP8266WebServer server;
  void handleMessage();
  void handleRoot();
  void handleNotFound();
public:
  WebController(unsigned long period) : UberAnimation(period), server(80) {
    // FIXME this is kinda hokey, do we really need methods?
    server.on("/message", HTTP_GET, [this]() { this->handleMessage(); });
    server.on("/", HTTP_GET,[this]() { this->handleRoot(); });
    server.onNotFound([this]() { this->handleNotFound(); });
    server.begin();
  }
  void update(unsigned long now) {
    server.handleClient();
    UberAnimation::update(now);
  }
};

void animationStartStop(Animation& animation, boolean start) {
  if (start) {
    animation.start();
  } else {
    animation.stop();
  }  
}

void WebController::handleMessage() {
  String newText = server.arg("text");
  ticker.setText(newText);
  String newColor = server.arg("color");
  if (newColor.equals("white")) {
    ticker.setTextColor(40, 40, 40);
  }
  if (newColor.equals("red")) {
    ticker.setTextColor(120, 0, 0);
  }
  if (newColor.equals("blue")) {
      ticker.setTextColor(0, 0, 120);
  }
  if (newColor.equals("green")) {
      ticker.setTextColor(0, 120, 0);
  }
  animationStartStop(ticker, server.arg("ticker").equals("on"));
  animationStartStop(stack, server.arg("stack").equals("on"));
  animationStartStop(plasma, server.arg("plasma").equals("on"));
  animationStartStop(pixel, server.arg("pixel").equals("on"));
  animationStartStop(face, server.arg("face").equals("on"));
  animationStartStop(sacred, server.arg("om").equals("on"));

  server.send(200, "text/html", page);  
}

void WebController::handleRoot() {
  server.send(200, "text/html", page);
}

void WebController::handleNotFound() {
  server.send(404, "text/plain", "nothing at this URI");
}

String WebController::page = "<! DOCTYPE html>\
<html>\
  <head>\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>Badge</title>\
    <style>\
      body { font-size: 200%; }\
      div { width: auto; padding: 0.1em 0; }\
      a { display: block; }\
      input, select { height: 100%, width: 100%; }\
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
        <div class=\"selection\">\
          <input name=\"ticker\" type=\"checkbox\" checked=\"checked\"/>\
          <span>Ticker</span>\
        </div>\
        <div class=\"selection\">\
          <input name=\"stack\" type=\"checkbox\" checked=\"checked\"/>\
          <span>Stack</span>\
        </div>\
        <div class=\"selection\">\
          <input name=\"plasma\" type=\"checkbox\" checked=\"checked\"/>\
          <span>Plasma</span>\
        </div>\
        <div class=\"selection\">\
          <input name=\"squares\" type=\"checkbox\" checked=\"checked\"/>\
          <span>Squares</span>\
        </div>\
        <div class=\"selection\">\
          <input name=\"face\" type=\"checkbox\" checked=\"checked\"/>\
          <span>Face</span>\
        </div>\
        <div class=\"selection\">\
          <input name=\"om\" type=\"checkbox\" checked=\"checked\"/>\
          <span>Om</span>\
        </div>\
        <button id=\"submit\">Set Message</button>\
      </form>\
    </div>\
  </body>\
</html>";

#endif WEBCONTROLLER_H

