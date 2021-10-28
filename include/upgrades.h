#ifndef UPGRADES_H
#define UPGRADES_H
#include <Arduino.h>

#define NUM_UPGRADES 14

#define UP_PICK 0
#define UP_DRILL 1
#define UP_CALCULATOR 2
#define UP_CHARM 3
#define UP_CONVEYOR_BELT 4
#define UP_CARGO 5
#define UP_DRILL_IDLE 6
#define UP_DRILL_BEARINGS 7
#define UP_DRILL_NITRO 8
#define UP_MOVE 9
#define UP_ACCOUNTANT 10
#define UP_MANAGER 11
#define UP_BRAIN 12
#define UP_DUMPER 13

#define UP_PICK_INITIAL_VALUE 1
#define UP_DRILL_INITIAL_VALUE 0
#define UP_CALCULATOR_INITIAL_VALUE 255
#define UP_CHARM_INITIAL_VALUE 0
#define UP_CONVEYOR_BELT_INITIAL_VALUE 1
#define UP_CARGO_INITIAL_VALUE 25
#define UP_DRILL_IDLE_INITIAL_VALUE 500
#define UP_DRILL_BEARINGS_INITIAL_VALUE 4
#define UP_DRILL_NITRO_INITIAL_VALUE 2
#define UP_MANAGER_INITIAL_VALUE 6000
#define UP_BRAIN_INITIAL_VALUE 0
#define UP_DUMPER_INITIAL_VALUE 0



#define UP_PICK_NUM_UPGRADES 6
const unsigned long UP_PICK_COST[] PROGMEM = {
  0, 
  200,601,1803,5415,16261
};
const unsigned long UP_PICK_VALUE[] PROGMEM = {
  UP_PICK_INITIAL_VALUE,
  2,4,8,16,32
};



#define UP_DRILL_NUM_UPGRADES 11
const unsigned long UP_DRILL_COST[] PROGMEM = {
  0, 
  50000,150000,450000,1350000,4050000,12150000,36450000,109350000,328050000,984150000
};
const unsigned long UP_DRILL_VALUE[] PROGMEM = {
  UP_DRILL_INITIAL_VALUE,
  50,100,200,400,800,1600,3200,6400,12800,25600
};


#define UP_CALCULATOR_NUM_UPGRADES 9
const unsigned long UP_CALCULATOR_COST[] PROGMEM = {0, 188,428,1090,2910,7914,21676,59520,163593};
const unsigned long UP_CALCULATOR_VALUE[] PROGMEM = {UP_CALCULATOR_INITIAL_VALUE, 146,84,48,27,16,9,5,0};


#define UP_CHARM_NUM_UPGRADES 4
const unsigned long UP_CHARM_COST[] PROGMEM = {0, 1000000, 10000000, 100000000 };
const unsigned long UP_CHARM_VALUE[] PROGMEM = {UP_CHARM_INITIAL_VALUE, 1, 2, 3 };

#define UP_CONVEYOR_BELT_NUM_UPGRADES 20
const unsigned long UP_CONVEYOR_BELT_COST[] PROGMEM = {
  0,
  200,388,809,1759,3894,8700,19512,43839,98576,221734,498839,1122324,2525167,5681563,12783454,28762709,64716032,145611011,327624711
};
const unsigned long UP_CONVEYOR_BELT_VALUE[] PROGMEM = {
  UP_CONVEYOR_BELT_INITIAL_VALUE,
  2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288
};

#define UP_DRILL_IDLE_NUM_UPGRADES 10
const unsigned long UP_DRILL_IDLE_COST[] PROGMEM = {
  0,
  60000,108000,194400,349920,629856,1133741,2040733,3673320,6611976
};

const unsigned long UP_DRILL_IDLE_VALUE[] PROGMEM = {
  UP_DRILL_IDLE_INITIAL_VALUE, 
  450,400,350,300,250,200,150,100,50
};

#define UP_DRILL_BEARINGS_NUM_UPGRADES 5
const unsigned long UP_DRILL_BEARINGS_COST[] PROGMEM = {0, 100000, 200000, 400000, 0xffffffff};
const unsigned long UP_DRILL_BEARINGS_VALUE[] PROGMEM = {UP_DRILL_BEARINGS_INITIAL_VALUE, 3, 2, 1, 0};

#define UP_DRILL_NITRO_NUM_UPGRADES 6
const unsigned long UP_DRILL_NITRO_COST[] PROGMEM = {
  0, 
  1000000,
  8000000,
  64000000,
  512000000,
  4096000000,
};
const unsigned long UP_DRILL_NITRO_VALUE[] PROGMEM = {UP_DRILL_NITRO_INITIAL_VALUE, 4, 8, 16, 32, 64};


#define UP_CARGO_NUM_UPGRADES 20
const unsigned long UP_CARGO_COST[] PROGMEM = {
  50,81,152,310,666,1467,3269,7323,16446,36972,83156,187071,420878,946944,2130592,4793801,10786022,24268518,54604135,122859273
};
const unsigned long UP_CARGO_VALUE[] PROGMEM = {
  25,48,90,171,326,619,1176,2235,4246,8067,15328,29123,55333,105132,199752,379528,721104,1370097,2603184,4946049
};

#define UP_MOVE_NUM_UPGRADES 4
const unsigned long UP_MOVE_COST[] PROGMEM = {0, 50000, 3200000, 36450000, 204800000};
const unsigned long UP_MOVE_VALUE[] PROGMEM = {0, 1, 2, 3, 4};


#define UP_ACCOUNTANT_NUM_UPGRADES 11
const unsigned long UP_ACCOUNTANT_COST[] PROGMEM = {
  0, 
  2000,5600,15680,43904,122931,344207,963781,2698586,7556040,21156912
};
const unsigned long UP_ACCOUNTANT_VALUE[] PROGMEM = {
  0,
  16,42,108,281,731,1901,4943,12851,33412,86872
};


#define UP_MANAGER_NUM_UPGRADES 11
const unsigned long UP_MANAGER_COST[] PROGMEM = {0, 5000,11000,24200,53240,117128,257682,566900,1247179,2743794,6036346};
const unsigned long UP_MANAGER_VALUE[] PROGMEM = {UP_MANAGER_INITIAL_VALUE, 
5500,5000,4500,4000,3500,3000,2500,2000,1500,1000};


#define UP_BRAIN_NUM_UPGRADES 11
const unsigned long UP_BRAIN_COST[] PROGMEM = {0,500,770,1283,2258,4110,7628,14314,27016,51151,97006};
const unsigned long UP_BRAIN_VALUE[] PROGMEM = {UP_BRAIN_INITIAL_VALUE, 1100,1000,900,800,700,600,500,400,300,200};


#define UP_DUMPER_NUM_UPGRADES 11
const unsigned long UP_DUMPER_COST[] PROGMEM = {0, 
1000,3000,9000,27000,81000,243000,729000,2187000,6561000,19683000 };
const unsigned long UP_DUMPER_VALUE[] PROGMEM = {UP_DUMPER_INITIAL_VALUE, 
60,138,317,730,1679,3862,8882,20429,46987,108069 };


const unsigned char NUM_UPGRADES_TABLE[] PROGMEM = {
  UP_PICK_NUM_UPGRADES,
  UP_DRILL_NUM_UPGRADES,
  UP_CALCULATOR_NUM_UPGRADES,
  UP_CHARM_NUM_UPGRADES,
  UP_CONVEYOR_BELT_NUM_UPGRADES,
  UP_CARGO_NUM_UPGRADES,
  UP_DRILL_IDLE_NUM_UPGRADES,
  UP_DRILL_BEARINGS_NUM_UPGRADES,
  UP_DRILL_NITRO_NUM_UPGRADES,
  UP_MOVE_NUM_UPGRADES,
  UP_ACCOUNTANT_NUM_UPGRADES,
  UP_MANAGER_NUM_UPGRADES,
  UP_BRAIN_NUM_UPGRADES,
  UP_DUMPER_NUM_UPGRADES
};

const unsigned long* const UP_COSTS[] PROGMEM = {
  UP_PICK_COST,
  UP_DRILL_COST,
  UP_CALCULATOR_COST,
  UP_CHARM_COST,
  UP_CONVEYOR_BELT_COST,
  UP_CARGO_COST,
  UP_DRILL_IDLE_COST,
  UP_DRILL_BEARINGS_COST,
  UP_DRILL_NITRO_COST,
  UP_MOVE_COST,
  UP_ACCOUNTANT_COST,
  UP_MANAGER_COST,
  UP_BRAIN_COST,
  UP_DUMPER_COST
};

const unsigned long* const UP_VALUES[] PROGMEM = {
  UP_PICK_VALUE,
  UP_DRILL_VALUE,
  UP_CALCULATOR_VALUE,
  UP_CHARM_VALUE,
  UP_CONVEYOR_BELT_VALUE,
  UP_CARGO_VALUE,
  UP_DRILL_IDLE_VALUE,
  UP_DRILL_BEARINGS_VALUE,
  UP_DRILL_NITRO_VALUE,
  UP_MOVE_VALUE,
  UP_ACCOUNTANT_VALUE,
  UP_MANAGER_VALUE,
  UP_BRAIN_VALUE,
  UP_DUMPER_VALUE
}; 

class Game;
typedef void (*UpgradeFunctionPtr)(Game* , const unsigned long);

unsigned char getNumUpgrades(unsigned char up);
unsigned long getUpgradeCost(unsigned char up, unsigned char level);
unsigned long getUpgradeValue(unsigned char up, unsigned char level);
UpgradeFunctionPtr getUpgradeFn(unsigned char up);

int getUpgradeFromMenuItem(unsigned char menuItem);

void upgradePick(Game* game, const unsigned long val);
void upgradeDrill(Game* game, const unsigned long val);
void upgradeCalculator(Game* game, const unsigned long val);
void upgradeCharm(Game* game, const unsigned long val);
void upgradeConveyorBelt(Game* game, const unsigned long val);
void upgradeCargo(Game* game, const unsigned long val);
void upgradeDrillIdle(Game* game, const unsigned long val);
void upgradeDrillBearings(Game* game, const unsigned long val);
void upgradeDrillNitro(Game* game, const unsigned long val);
void upgradeMove(Game* game, const unsigned long val);
void upgradeAccountant(Game* game, const unsigned long val);
void upgradeManager(Game* game, const unsigned long val);
void upgradeBrain(Game* game, const unsigned long val);
void upgradeDumper(Game* game, const unsigned long val);

const UpgradeFunctionPtr PROGMEM UP_UPGRADE_FUNCTIONS[] = {
  &upgradePick,
  &upgradeDrill,
  &upgradeCalculator,
  &upgradeCharm,
  &upgradeConveyorBelt,
  &upgradeCargo,
  &upgradeDrillIdle,
  &upgradeDrillBearings,
  &upgradeDrillNitro,
  &upgradeMove,
  &upgradeAccountant,
  &upgradeManager,
  &upgradeBrain,
  &upgradeDumper,
};

#endif