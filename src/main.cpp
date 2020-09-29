#include <Arduino.h>
#include "game.h"

Game game;

void setup() {
  randomSeed(analogRead(A2));
  game.init();
}

void loop() {
  game.update();
}