#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "BeetleBot";
const char* password = "12345678";

ESP8266WebServer server(80);

/* ===== 网页 ===== */
const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body{font-family:Arial;text-align:center;}
button{
  width:90px;height:60px;
  font-size:16px;
  margin:6px;
}
</style>
</head>
<body>

<h3>机器人控制</h3>

<button onclick="cmd('1')">前进</button><br>
<button onclick="cmd('4')">向左</button>
<button onclick="cmd('3')">向右</button><br>
<button onclick="cmd('2')">后退</button><br><br>

<button onclick="cmd('7')">自动</button>
<button onclick="cmd('6')">进攻</button><br>

<button onclick="cmd('8')">超声波</button>
<button onclick="cmd('5')">稳定运行</button>

<script>
function cmd(c){
  fetch('/cmd?c='+c);
}
</script>

</body>
</html>
)rawliteral";


void handleRoot() {
  server.send_P(200, "text/html", PAGE);
}

void handleCmd() {
  if (server.hasArg("c")) {
    char c = server.arg("c")[0];
    Serial.println(c);   // 发给 Arduino
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/cmd", handleCmd);
  server.begin();
}

void loop() {
  server.handleClient();
}
