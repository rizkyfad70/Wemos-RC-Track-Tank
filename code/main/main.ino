/* main */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

#include "motor_control.h"
#include "websocket_server.h"
#include "web_page.h"
#include "buzzer_control.h"

// AP credentials
const char* ssid = "Mobil_Ehsan";
const char* password = "12345678";

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

void setup() {
  Serial.begin(115200);

  // Pin setup motor & LED
  motorSetup();

  // Setup WiFi AP
  WiFi.softAP(ssid, password);
  Serial.println("AP started: " + String(ssid));

  // WebSocket
  webSocket.begin();
  initWebSocket(webSocket);

  // WebServer
  server.on("/", [](){ server.send(200, "text/html", htmlPage); });
  server.begin();
  Serial.println("Server started");
}

void loop() {
  webSocket.loop();
  server.handleClient();
  motorLoop(); // update motor setiap loop
  buzzerLoop();
}
