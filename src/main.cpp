#include <Arduino.h>
#include "game.h"

Game game;

void setup() {
  game.init();
}

void loop() {
  game.update();
}