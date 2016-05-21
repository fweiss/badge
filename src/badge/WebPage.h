String page = "<! DOCTYPE html>\
<html>\
  <head>\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
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

