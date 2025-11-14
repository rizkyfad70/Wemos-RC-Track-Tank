/* motor_control.cpp */
#include <Arduino.h>
#include "motor_control.h"

String motorCmd = "STOP";
int motorSpeed = 512;

void motorSetup() {
  pinMode(LED_BUILTIN_PIN, OUTPUT);
  digitalWrite(LED_BUILTIN_PIN, LOW);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);


  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void setMotorCmd(String cmd) {
  motorCmd = cmd;
}

void setMotorSpeed(int speed) {
  motorSpeed = constrain(speed, 0, PWM_MAX);
}

void motorLoop() {
  int pwmA = motorSpeed;
  int pwmB = motorSpeed;

  if (motorCmd == "RIGHT") {
    analogWrite(AIN1, pwmA); analogWrite(AIN2, 0);
    analogWrite(BIN1, pwmB); analogWrite(BIN2, 0);
  } else if (motorCmd == "LEFT") {
    analogWrite(AIN1, 0); analogWrite(AIN2, pwmA);
    analogWrite(BIN1, 0); analogWrite(BIN2, pwmB);
  } else if (motorCmd == "BACK") {
    analogWrite(AIN1, 0); analogWrite(AIN2, pwmA);
    analogWrite(BIN1, pwmB); analogWrite(BIN2, 0);
  } else if (motorCmd == "FWD") {
    analogWrite(AIN1, pwmA); analogWrite(AIN2, 0);
    analogWrite(BIN1, 0); analogWrite(BIN2, pwmB);
  } else if (motorCmd == "STOP") {
    analogWrite(AIN1, 0); analogWrite(AIN2, 0);
    analogWrite(BIN1, 0); analogWrite(BIN2, 0);
  }
}
