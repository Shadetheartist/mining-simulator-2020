#ifndef GAME_H
#define GAME_H

#include "interface.h"
#include "gameboard.h"
#include "resources.h"
#include "upgrades.h"

class Interface;

struct GameState {
  unsigned char currentLocation;
  unsigned char numMinedPerPickUse;
  unsigned char cargoSellDelay;
  unsigned char drillIdle;
  unsigned char drillTempDecrease;
  unsigned char drillNitro;
  unsigned char filter;
  unsigned char accountants;
  unsigned char managers;
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
        unsigned char menuSelectedWindow;
        unsigned char menuWindowOption;
        unsigned char drillFrame;

        float drillTemp;
        unsigned int maxDrillTemp;
        unsigned char drillTempIncrase;
        unsigned long lastDrillDecreaseMs;
        
        unsigned long accountantSellMs;

        GameState state;
        Interface *interface;
        Gameboard *gameboard;
        
        Game();

        void init();
        void update();
        void menuUpdate();
        void err();
        void showMenu();
        unsigned long getCargoPercentage();
        void sellCargo();
        void addMoney(const unsigned long amount);
        void upgrade(const unsigned char up);
        void drillPassive();
        void accountantPassive();

        char getRandomResource();
        char mine(unsigned long amount);
        void pick();
        void drill();

        void save();
        void load();
};

#endif