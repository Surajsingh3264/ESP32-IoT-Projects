#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "pins.h"
#include "webpage.h"

AsyncWebServer server(80);

int motorSpeed=180;
bool headlights=false;
bool horn=false;

//================ MOTOR =================

void stopMotor(){
  digitalWrite(STBY,LOW);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
  ledcWrite(PWMA,0);
  ledcWrite(PWMB,0);
}

void forward(){
  digitalWrite(STBY,HIGH);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  ledcWrite(PWMA,motorSpeed);
  ledcWrite(PWMB,motorSpeed);
}

void backward(){
  digitalWrite(STBY,HIGH);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  ledcWrite(PWMA,motorSpeed);
  ledcWrite(PWMB,motorSpeed);
}

void left(){
  digitalWrite(STBY,HIGH);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  ledcWrite(PWMA,motorSpeed);
  ledcWrite(PWMB,motorSpeed);
}

void right(){
  digitalWrite(STBY,HIGH);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  ledcWrite(PWMA,motorSpeed);
  ledcWrite(PWMB,motorSpeed);
}

//================ LIGHT =================

void lightOn(){
  headlights=true;
  digitalWrite(HEADLIGHT_PIN,HIGH);
}

void lightOff(){
  headlights=false;
  digitalWrite(HEADLIGHT_PIN,LOW);
}

//================ HORN =================

void hornOn(){
  horn=true;
  digitalWrite(BUZZER_PIN,HIGH);
}

void hornOff(){
  horn=false;
  digitalWrite(BUZZER_PIN,LOW);
}

//================ BATTERY =================

int batteryPercentage(){
  int adc=analogRead(BATTERY_PIN);
  int p=map(adc,2200,3100,0,100);
  return constrain(p,0,100);
}
//================ SETUP =================

void setup(){

  Serial.begin(115200);

  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(STBY,OUTPUT);

  pinMode(HEADLIGHT_PIN,OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(BATTERY_PIN,INPUT);

  digitalWrite(STBY,LOW);
  digitalWrite(HEADLIGHT_PIN,LOW);
  digitalWrite(BUZZER_PIN,LOW);

  ledcAttach(PWMA,PWM_FREQ,PWM_RESOLUTION);
  ledcAttach(PWMB,PWM_FREQ,PWM_RESOLUTION);

  stopMotor();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_NAME,WIFI_PASSWORD);

  server.on("/",HTTP_GET,[](AsyncWebServerRequest *request){
    request->send_P(200,"text/html",webpage);
  });

  server.on("/forward",HTTP_GET,[](AsyncWebServerRequest *request){
    forward();
    request->send(200,"text/plain","OK");
  });

  server.on("/backward",HTTP_GET,[](AsyncWebServerRequest *request){
    backward();
    request->send(200,"text/plain","OK");
  });

  server.on("/left",HTTP_GET,[](AsyncWebServerRequest *request){
    left();
    request->send(200,"text/plain","OK");
  });

  server.on("/right",HTTP_GET,[](AsyncWebServerRequest *request){
    right();
    request->send(200,"text/plain","OK");
  });

  server.on("/stop",HTTP_GET,[](AsyncWebServerRequest *request){
    stopMotor();
    request->send(200,"text/plain","OK");
  });
    server.on("/light/on",HTTP_GET,[](AsyncWebServerRequest *request){
    lightOn();
    request->send(200,"text/plain","OK");
  });

  server.on("/light/off",HTTP_GET,[](AsyncWebServerRequest *request){
    lightOff();
    request->send(200,"text/plain","OK");
  });

  server.on("/horn/on",HTTP_GET,[](AsyncWebServerRequest *request){
    hornOn();
    request->send(200,"text/plain","OK");
  });

  server.on("/horn/off",HTTP_GET,[](AsyncWebServerRequest *request){
    hornOff();
    request->send(200,"text/plain","OK");
  });

  server.on("/speed",HTTP_GET,[](AsyncWebServerRequest *request){
    if(request->hasParam("value")){
      motorSpeed=request->getParam("value")->value().toInt();
      motorSpeed=constrain(motorSpeed,0,255);
    }
    request->send(200,"text/plain","OK");
  });

  server.on("/status",HTTP_GET,[](AsyncWebServerRequest *request){
    String json="{";
    json+="\"battery\":";
    json+=batteryPercentage();
    json+=",";
    json+="\"connected\":true";
    json+="}";
    request->send(200,"application/json",json);
  });

  server.begin();
}

void loop(){

}
