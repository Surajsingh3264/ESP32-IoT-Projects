#include <WiFi.h>
#include <WebServer.h>

#include "pins.h"
#include "webpage.h"

WebServer server(80);

int motorSpeed = 180;

bool headlights = false;

void forward()
{
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    ledcWrite(PWM_CHANNEL_A, motorSpeed);
    ledcWrite(PWM_CHANNEL_B, motorSpeed);
}
void backward()
{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, motorSpeed);
    ledcWrite(PWM_CHANNEL_B, motorSpeed);
}
void left()
{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    ledcWrite(PWM_CHANNEL_A, motorSpeed);
    ledcWrite(PWM_CHANNEL_B, motorSpeed);
}
void right()
{
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, motorSpeed);
    ledcWrite(PWM_CHANNEL_B, motorSpeed);
}
void stopMotor()
{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    ledcWrite(PWM_CHANNEL_A, 0);
    ledcWrite(PWM_CHANNEL_B, 0);
}
void lightOn()
{
    headlights = true;
    digitalWrite(HEADLIGHT_PIN, HIGH);
}
void lightOff()
{
    headlights = false;
    digitalWrite(HEADLIGHT_PIN, LOW);
}
void hornOn()
{
    digitalWrite(BUZZER_PIN, HIGH);
}
void hornOff()
{
    digitalWrite(BUZZER_PIN, LOW);
}
int batteryPercentage()
{
    int adc = analogRead(BATTERY_PIN);
    return map(adc, 2200, 3100, 0, 100);
}
