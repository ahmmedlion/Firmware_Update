#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

// Wi-Fi credentials
const char* ssid = "Tech_Talk_V1";
const char* password = "hashi&Lion";

// Host name
const char* host = "lionahmmed";

// Create an instance of WebServer
WebServer server(80);

// Login page
const char* loginIndex = 
"<form name='loginForm'>"
    "<table width='20%' bgcolor='F0F7F7' align='center'>"
        "<tr>"
            "<td colspan=2>"
                "<center><font size=4><b>Lion Ahmmed</b></font></center>"
                "<br>"
            "</td>"
            "<br>"
            "<br>"
        "</tr>"
        "<td>Username:</td>"
        "<td><input type='text' size=25 name='userid'><br></td>"
        "</tr>"
        "<br>"
        "<br>"
        "<tr>"
            "<td>Password:</td>"
            "<td><input type='Password' size=25 name='pwd'><br></td>"
            "<br>"
            "<br>"
        "</tr>"
        "<tr>"
            "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
        "</tr>"
    "</table>"
"</form>"
"<script>"
    "function check(form) {"
    "if(form.userid.value=='Lion' && form.pwd.value=='Lion') {"
    "window.open('/serverIndex')"
    "} else {"
    "alert('Error Password or Username')"
    "}"
    "}"
"</script>";

// Combined Server Index and Restart Page
const char* combinedPage = 
"<html>"
// "<head><title>Hardware Management</title></head>"
"<body>"
"<h1><centre>Hardware Management</h1>"
"<h2>Firmware Update</h2>"
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
   "<input type='file' name='update'>"
   "<input type='submit' value='Update'>"
"</form>"
"<div id='prg'>progress: 0%</div>"
"<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  "$.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')"
  "},"
  "error: function (a, b, c) {"
  "}"
  "});"
  "});"
          "</tr>"
        "<tr>"
                "</tr>"
        "<tr>"
                "</tr>"
        "<tr>"
"</script>"
"<h2>Restart Device</h2>"
"<button onclick='confirmRestart()'>Restart</button>"
"<script>"
"function confirmRestart() {"
"if (confirm('Are you sure you want to restart the device?')) {"
"restartESP();"
"}"
"}"
"function restartESP() {"
"fetch('/restart').then(response => response.text()).then(data => alert(data));"
"}"
"</script>"
"</body>"
"</html>";

void setup(void) {
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Use mDNS for host name resolution
  if (!MDNS.begin(host)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  // Serve login page
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });

  // Serve combined page
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", combinedPage);
  });

  // Handle firmware update
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { // Start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      // Flashing firmware to ESP
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { // True to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });

  // Handle restart request
  server.on("/restart", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "Restarting ESP32...");
    ESP.restart();
  });

  server.begin();
}

void loop(void) {
  server.handleClient();
  delay(1);
}
