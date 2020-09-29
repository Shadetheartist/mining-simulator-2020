#ifndef GAME_H
#define GAME_H

#include "interface.h"
#include "gameboard.h"
#include "resources.h"
#include "upgrades.h"

class Interface;

struct GameState {
  unsigned char currentLocation;
  unsigned int numMinedPerPickUse;
  unsigned char cargoSellDelay;
  unsigned int drillIdle;
  unsigned char drillTempDecrease;
  unsigned char drillNitro;
  unsigned char filter;
  unsigned char accountants;
  unsigned char managers;
  unsigned int brain;
  unsigned char upgrades[NUM_UPGRADES];
  
  float maxCargo;
  float money;

  unsigned long numMinedPerDrillUse;
  unsigned long cargoSoldPerIteration;

  float cargo[NUM_RESOURCES];
  
};

class Game {
    public:
        static bool shouldDraw;
        bool isShowingMenu;
        unsigned char menuSelectedOption;
        unsigned char menuSelectedPage;
        unsigned char drillFrame;
        unsigned char pickFrame;

        float drillTemp;
        unsigned int maxDrillTemp;
        unsigned char drillTempIncrase;
        unsigned long lastDrillDecreaseMs;

        bool cargoChanged;
        unsigned long lastCargoPercentage;
        
        unsigned long accountantSellMs;
        unsigned long lastBrainPickMs;
        unsigned long lastDrillIdleUs;

        GameState state;
        Interface *interface;
        Gameboard *gameboard;
        
        Game();

        void init();
        void update();
        void menuUpdate();
        float getTotalCargo();
        unsigned long getCargoPercentage();
        void sellCargo();
        void addMoney(const unsigned long amount);
        void upgrade(const unsigned char up);
        void drillPassive();
        void drillIdleSound();
        void accountantPassive();

        char getRandomResource();
        char mine(unsigned long amount);
        void pick();
        void drill();

        void save();
        void load();
};

#endif