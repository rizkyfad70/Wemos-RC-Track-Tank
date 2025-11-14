/* websocket_server.cpp */
#include <Arduino.h>
#include "websocket_server.h"
#include "motor_control.h"
#include "buzzer_control.h"

void handleWSMessage(uint8_t num, uint8_t * payload, size_t length) {
  String cmd = String((char*)payload).substring(0, length);
  Serial.println("Command: " + cmd);

  if (cmd == "LED_ON") digitalWrite(LED_BUILTIN_PIN, HIGH);
  else if (cmd == "LED_OFF") digitalWrite(LED_BUILTIN_PIN, LOW);
  else if (cmd == "FWD" || cmd == "BACK" || cmd == "LEFT" || cmd == "RIGHT" || cmd == "STOP")
    setMotorCmd(cmd);
  else if (cmd.startsWith("SPEED:")) setMotorSpeed(cmd.substring(6).toInt());
  else if (cmd == "SONG1") buzzerPlay(1);
  else if (cmd == "SONG2") buzzerPlay(2);
  else if (cmd == "STOP_SONG") buzzerStop();
}

void onWS(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if(type == WStype_TEXT) handleWSMessage(num, payload, length);
}

void initWebSocket(WebSocketsServer &webSocket) {
  webSocket.onEvent(onWS);
}
