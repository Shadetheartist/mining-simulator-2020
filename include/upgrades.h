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
#define UP_MANAGER_INITIAL_VALUE 6
#define UP_BRAIN_INITIAL_VALUE 0
#define UP_DUMPER_INITIAL_VALUE 0


#define UP_PICK_NUM_UPGRADES 5
const unsigned long UP_PICK_COST[] PROGMEM = {
  0, 
  50,200,800,3200,12800
};
const unsigned long UP_PICK_VALUE[] PROGMEM = {
  UP_PICK_INITIAL_VALUE,
  2,4,8,16,32
};


#define UP_DRILL_NUM_UPGRADES 11
const unsigned long UP_DRILL_COST[] PROGMEM = {
  0, 
  20000,70000,245000,857500,3001250,10504375,36765313,128678594,450375078,1576312773
};
const unsigned long UP_DRILL_VALUE[] PROGMEM = {
  UP_DRILL_INITIAL_VALUE,
  16,28,49,86,150,263,460,804,1407,2463
};


#define UP_CALCULATOR_NUM_UPGRADES 10
const unsigned long UP_CALCULATOR_COST[] PROGMEM = {0, 188,428,1090,2910,7914,21676,59520,163593,449793};
const unsigned long UP_CALCULATOR_VALUE[] PROGMEM = {UP_CALCULATOR_INITIAL_VALUE, 146,84,48,27,16,9,5,3,2};


#define UP_CHARM_NUM_UPGRADES 4
const unsigned long UP_CHARM_COST[] PROGMEM = {0, 100000, 1000000, 10000000 };
const unsigned long UP_CHARM_VALUE[] PROGMEM = {UP_CHARM_INITIAL_VALUE, 1, 2, 3 };


#define UP_CONVEYOR_BELT_NUM_UPGRADES 20
const unsigned long UP_CONVEYOR_BELT_COST[] PROGMEM = {
  0,
  250,400,700,1300,2500,4900,9700,19300,38500,76900,153700,307300,614500,1228900,2457700,4915300,9830500,19660900,39321700,78643300
};
const unsigned long UP_CONVEYOR_BELT_VALUE[] PROGMEM = {
  UP_CONVEYOR_BELT_INITIAL_VALUE,
  2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288
};


#define UP_DRILL_IDLE_NUM_UPGRADES 10
const unsigned long UP_DRILL_IDLE_COST[] PROGMEM = {
  0,
  10000,
  20000,
  40000,
  80000,
  160000,
  320000,
  640000,
  1280000,
  2560000,
};

const unsigned long UP_DRILL_IDLE_VALUE[] PROGMEM = {
  UP_DRILL_IDLE_INITIAL_VALUE, 
  450,
  400,
  350,
  300,
  250,
  200,
  150,
  100,
  50,
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
  25,44,77,134,234,410,718,1257,2199,3848,6735,11786,20625,36094,63164,110538,193441,338522,592413,1036723
};

#define UP_MOVE_NUM_UPGRADES 4
const unsigned long UP_MOVE_COST[] PROGMEM = {0, 50000, 3200000, 36450000, 204800000};
const unsigned long UP_MOVE_VALUE[] PROGMEM = {0, 1, 2, 3, 4};


#define UP_ACCOUNTANT_NUM_UPGRADES 11
const unsigned long UP_ACCOUNTANT_COST[] PROGMEM = {
  0, 
  2000,4500,10125,22781,51258,115330,259493,583859,1313682,2955784
};
const unsigned long UP_ACCOUNTANT_VALUE[] PROGMEM = {
  0,
  25,45,81,146,262,472,850,1531,2755,4959
};

#define UP_MANAGER_NUM_UPGRADES 6
const unsigned long UP_MANAGER_COST[] PROGMEM = {0, 50000, 250000, 250000 * 5, 250000 * 5 * 5, 250000 * 5 * 5 * 5};
const unsigned long UP_MANAGER_VALUE[] PROGMEM = {UP_MANAGER_INITIAL_VALUE, 5, 4, 3, 2, 1};



#define UP_BRAIN_NUM_UPGRADES 11
const unsigned long UP_BRAIN_COST[] PROGMEM = {0,500,770,1283,2258,4110,7628,14314,27016,51151,97006};
const unsigned long UP_BRAIN_VALUE[] PROGMEM = {UP_BRAIN_INITIAL_VALUE, 1100,1000,900,800,700,600,500,400,300,200};



#define UP_DUMPER_NUM_UPGRADES 11
const unsigned long UP_DUMPER_COST[] PROGMEM = {0, 
1000,2200,4840,10648,23426,51536,113380,249436,548759,1207269 };
const unsigned long UP_DUMPER_VALUE[] PROGMEM = {UP_DUMPER_INITIAL_VALUE, 
100,175,306,536,938,1641,2872,5027,8796,15394 };


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