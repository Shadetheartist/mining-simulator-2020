#include "gameboard.h"
#include "resources.h"
#include <Arduino.h>

Gameboard::Gameboard()
{
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN_1, OUTPUT);
  pinMode(PIN_LED_GREEN_2, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_CLICKER, OUTPUT);

  triggerBtn.attach(PIN_TRIGGER, INPUT);
  triggerBtn.interval(DEBOUNCE_MS);

  dpadUpBtn.attach(PIN_DPAD_UP, INPUT);
  dpadUpBtn.interval(DEBOUNCE_MS);

  dpadDownBtn.attach(PIN_DPAD_DOWN, INPUT);
  dpadDownBtn.interval(DEBOUNCE_MS);

  dpadMiddleBtn.attach(PIN_DPAD_MIDDLE, INPUT);
  dpadMiddleBtn.interval(DEBOUNCE_MS);

  boostBtn.attach(PIN_BOOST, INPUT);
  boostBtn.interval(DEBOUNCE_MS);
  
  mute = false;
}

void playTone(unsigned int d){
  digitalWrite(PIN_CLICKER, HIGH);
  delayMicroseconds(d);
  digitalWrite(PIN_CLICKER, LOW);
  delayMicroseconds(d);
}

void Gameboard::triggerDrillSound(char resource){
  triggerPickSound(resource);
}

void Gameboard::triggerClickSound(){
  if(mute){ return; }
  playTone(10);
}

void Gameboard::triggerBadSound(){
  if(mute){ return; }
  
  for(unsigned char i = 0; i < 16; i++){
    playTone(500);
  }
}

void Gameboard::triggerMeepSound(){
  if(mute){ return; }
  
  for(int i = 0; i < 2; i++){
    playTone(1000);
  }
}

void Gameboard::triggerDumpSound(){
  if(mute){ return; }

  for(int i = 0; i < 2; i++){
    playTone(1200);
  }
  
  for(int i = 0; i < 4; i++){
    playTone(2400);
  }
}

void Gameboard::triggerPickSound(char resource){
  if(mute){ return; }
  if(resource == -1){ return; }

  int d = 0;
  int n = 0;
  switch (resource)
  {
  case 0:
    n = 1;
    d = 500;
    break;
  
  default:
    n = 2;
    d = 2000 / resource;
    break;
  }
  
  for(int i = 0; i < n; i++){
    playTone(d);
  }
}


void Gameboard::triggerMoneySound(){
  if(mute){ return; }

  for(int i = 0; i < 5; i++){
    playTone(150);
  }
}

void Gameboard::triggerSpendSound(){
  if(mute){ return; }

  for(int i = 0; i < 16; i++){
    playTone(200);
  }
  
  delay(50);

  for(int i = 0; i < 16; i++){
    playTone(500);
  }
  
}

void Gameboard::setRedLED(uint8_t val){
  digitalWrite(PIN_LED_RED, val);
}

void Gameboard::setUpperGreenLED(const uint8_t val){
  digitalWrite(PIN_LED_GREEN_1, val);
}

void Gameboard::setLowerGreenLED(const uint8_t val){
  digitalWrite(PIN_LED_GREEN_2, val);
}

void Gameboard::setBlueLED(const uint8_t val){
  digitalWrite(PIN_LED_BLUE, val);
}
