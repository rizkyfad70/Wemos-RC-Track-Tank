/* motor_control.h */
#pragma once

#define AIN1 D6
#define AIN2 D5
#define BIN1 D2
#define BIN2 D1
#define LED_BUILTIN_PIN D0
#define BUZZER_PIN D7

#define PWM_MAX 1023

void motorSetup();
void motorLoop();
void setMotorCmd(String cmd);
void setMotorSpeed(int speed);
