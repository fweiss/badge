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
        <div class=\"selection\">\
          <input name=\"ticker\" type=\"checkbox\"/>\
          <span>Ticker</span>\
        </div>\
        <div class=\"selection\">\
          <input name=\"squares\" type=\"checkbox\"/>\
          <span>Squares</span>\
        </div>\
        <div class=\"selection\">\
          <input name=\"plasma\" type=\"checkbox\"/>\
          <span>Plasma</span>\
        </div>\
        <button id=\"submit\">Set Message</button>\
      </form>\
    </div>\
  </body>\
</html>";

