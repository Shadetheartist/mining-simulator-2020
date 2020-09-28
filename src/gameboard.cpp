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

  dpadLeftBtn.attach(PIN_DPAD_LEFT, INPUT);
  dpadLeftBtn.interval(DEBOUNCE_MS);

  dpadRightBtn.attach(PIN_DPAD_RIGHT, INPUT);
  dpadRightBtn.interval(DEBOUNCE_MS);

  dpadMiddleBtn.attach(PIN_DPAD_MIDDLE, INPUT);
  dpadMiddleBtn.interval(DEBOUNCE_MS);

  boostBtn.attach(PIN_BOOST, INPUT);
  boostBtn.interval(DEBOUNCE_MS);
  
  mute = false;
}

void Gameboard::triggerDrillSound(unsigned char resource){
  if(mute){ return; }
  
  triggerPickSound(resource);
}

void Gameboard::triggerClickSound(){
  if(mute){ return; }
  
  digitalWrite(PIN_CLICKER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_CLICKER, LOW);
}

void Gameboard::triggerBadSound(){
  if(mute){ return; }
  
  for(unsigned char i = 0; i < 16; i++){
    digitalWrite(PIN_CLICKER, HIGH);
    delayMicroseconds(100);
    digitalWrite(PIN_CLICKER, LOW); 
    delayMicroseconds(10);
  }
}

void Gameboard::triggerMeepSound(){
  if(mute){ return; }
  
  for(int i = 0; i < 3; i++){
    digitalWrite(PIN_CLICKER, HIGH);
    delay(1);
    digitalWrite(PIN_CLICKER, LOW); 
    delay(1);
  }
}

void Gameboard::triggerPickSound(unsigned char resource){
  if(mute){ return; }

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
    digitalWrite(PIN_CLICKER, HIGH);
    delayMicroseconds(d);
    digitalWrite(PIN_CLICKER, LOW); 
    delayMicroseconds(d);
  }
}


void Gameboard::triggerMoneySound(){
  if(mute){ return; }

  for(int i = 0; i < 8; i++){
    digitalWrite(PIN_CLICKER, HIGH);
    delayMicroseconds(500);
    digitalWrite(PIN_CLICKER, LOW); 
    delayMicroseconds(500);
  }
  
  delay(20);

  for(int i = 0; i < 100; i++){
    digitalWrite(PIN_CLICKER, HIGH);
    delayMicroseconds(100);
    digitalWrite(PIN_CLICKER, LOW); 
    delayMicroseconds(100);
  }
}

void Gameboard::triggerSpendSound(){
  if(mute){ return; }

  for(int i = 0; i < 16; i++){
    digitalWrite(PIN_CLICKER, HIGH);
    delayMicroseconds(200);
    digitalWrite(PIN_CLICKER, LOW); 
    delayMicroseconds(200);
  }
  
  delay(50);

  for(int i = 0; i < 16; i++){
    digitalWrite(PIN_CLICKER, HIGH);
    delayMicroseconds(500);
    digitalWrite(PIN_CLICKER, LOW); 
    delayMicroseconds(500);
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
