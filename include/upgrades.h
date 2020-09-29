#ifndef UPGRADES_H
#define UPGRADES_H
#include <Arduino.h>

#define NUM_UPGRADES 13

#define UP_PICK 0
#define UP_DRILL 1
#define UP_CALCULATOR 2
#define UP_FILTER 3
#define UP_CONVEYOR_BELT 4
#define UP_CARGO 5
#define UP_DRILL_IDLE 6
#define UP_DRILL_BEARINGS 7
#define UP_DRILL_NITRO 8
#define UP_MOVE 9
#define UP_ACCOUNTANT 10
#define UP_MANAGER 11
#define UP_BRAIN 12

#define UP_PICK_INITIAL_VALUE 1
#define UP_DRILL_INITIAL_VALUE 0
#define UP_CALCULATOR_INITIAL_VALUE 255
#define UP_FILTER_INITIAL_VALUE 0
#define UP_CONVEYOR_BELT_INITIAL_VALUE 1
#define UP_CARGO_INITIAL_VALUE 25
#define UP_DRILL_IDLE_INITIAL_VALUE 500
#define UP_DRILL_BEARINGS_INITIAL_VALUE 4
#define UP_DRILL_NITRO_INITIAL_VALUE 2
#define UP_MANAGER_INITIAL_VALUE 30
#define UP_BRAIN_INITIAL_VALUE 0

#define UP_PICK_NUM_UPGRADES 11
const unsigned long UP_PICK_COST[] PROGMEM = {
  0, 
  50,
  200,
  800,
  3200,
  12800,
  51200,
  204800,
  819200,
  3276800,
  13107200,
};
const unsigned long UP_PICK_VALUE[] PROGMEM = {
  UP_PICK_INITIAL_VALUE,
  2,
  4,
  8,
  16,
  32,
  64,
  128,
  256,
  512,
  1024,
};

#define UP_DRILL_NUM_UPGRADES 11
const unsigned long UP_DRILL_COST[] PROGMEM = {
  0, 
  12500,
  25000,
  100000,
  400000,
  1600000,
  6400000,
  25600000,
  102400000,
  409600000,
  1638400000,
};
const unsigned long UP_DRILL_VALUE[] PROGMEM = {
  UP_DRILL_INITIAL_VALUE,
  16,
  32,
  64,
  128,
  256,
  512,
  1024,
  2048,
  4096,
  8192,
};

#define UP_CALCULATOR_NUM_UPGRADES 7
const unsigned long UP_CALCULATOR_COST[] PROGMEM = {0, 50, 100, 200, 400, 800, 1600};
const unsigned long UP_CALCULATOR_VALUE[] PROGMEM = {UP_CALCULATOR_INITIAL_VALUE, 128, 64, 32, 16, 8, 0};

#define UP_FILTER_NUM_UPGRADES 9
const unsigned long UP_FILTER_COST[] PROGMEM = {0, 100000, 200000, 400000, 8000000, 1600000, 3200000, 6400000, 12800000 };
const unsigned long UP_FILTER_VALUE[] PROGMEM = {UP_FILTER_INITIAL_VALUE, 1, 2, 3, 4, 5, 6, 7, 8 };

#define UP_CONVEYOR_BELT_NUM_UPGRADES 25
const unsigned long UP_CONVEYOR_BELT_COST[] PROGMEM = {
  0,
  250,
  500,
  1000,
  2000,
  4000,
  8000,
  16000,
  32000,
  64000,
  128000,
  256000,
  512000,
  1024000,
  2048000,
  4096000,
  8192000,
  16384000,
  32768000,
  65536000,
  131072000,
  262144000,
  524288000,
  1048576000,
  2097152000,
};
const unsigned long UP_CONVEYOR_BELT_VALUE[] PROGMEM = {
  UP_CONVEYOR_BELT_INITIAL_VALUE,
  2,
  4,
  8,
  16,
  32,
  64,
  128,
  256,
  512,
  1024,
  2048,
  4096,
  8192,
  16384,
  32768,
  65536,
  131072,
  262144,
  524288,
  1048576,
  2097152,
  4194304,
  8388608,
  16777216,
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

#define UP_CARGO_NUM_UPGRADES 25
const unsigned long UP_CARGO_COST[] PROGMEM = {
  0,
  25,
  50,
  100,
  200,
  400,
  800,
  1600,
  3200,
  6400,
  12800,
  25600,
  51200,
  102400,
  204800,
  409600,
  819200,
  1638400,
  3276800,
  6553600,
  13107200,
  26214400,
  52428800,
  104857600,
  209715200,
};

const unsigned long UP_CARGO_VALUE[] PROGMEM = {
  25,
  50,
  100,
  200,
  400,
  800,
  1600,
  3200,
  6400,
  12800,
  25600,
  51200,
  102400,
  204800,
  409600,
  819200,
  1638400,
  3276800,
  6553600,
  13107200,
  26214400,
  52428800,
  104857600,
  209715200,
  419430400,
};

#define UP_MOVE_NUM_UPGRADES 5
const unsigned long UP_MOVE_COST[] PROGMEM = {
  0,
  50000,
  500000,
  5000000,
  50000000,
  500000000
};
const unsigned long UP_MOVE_VALUE[] PROGMEM = {0, 1, 2, 3, 4};

#define UP_ACCOUNTANT_NUM_UPGRADES 11
const unsigned long UP_ACCOUNTANT_COST[] PROGMEM = {
  0, 
  50000,
  100000,
  200000,
  400000,
  800000,
  1600000,
  3200000,
  6400000,
  12800000,
  25600000,
  51200000,
  102400000,
  204800000,
  409600000,
  819200000,
  1638400000,
  3276800000,
};
const unsigned long UP_ACCOUNTANT_VALUE[] PROGMEM = {
  0, 
  1000,
  2000,
  4000,
  8000,
  16000,
  32000,
  64000,
  128000,
  256000,
  512000,
  1024000,
  2048000,
  4096000,
  8192000,
  16384000,
  32768000,
  65536000,
  131072000,
  262144000,
  524288000,
};

#define UP_MANAGER_NUM_UPGRADES 6
const unsigned long UP_MANAGER_COST[] PROGMEM = {0, 50000, 250000, 250000 * 5, 250000 * 5 * 5, 250000 * 5 * 5 * 5};
const unsigned long UP_MANAGER_VALUE[] PROGMEM = {UP_MANAGER_INITIAL_VALUE, 25, 20, 15, 10, 5};


#define UP_BRAIN_NUM_UPGRADES 5
const unsigned long UP_BRAIN_COST[] PROGMEM = {0, 100, 1000, 10000, 100000};
const unsigned long UP_BRAIN_VALUE[] PROGMEM = {UP_BRAIN_INITIAL_VALUE, 4000, 3000, 2000, 1000};


const unsigned char NUM_UPGRADES_TABLE[] PROGMEM = {
  UP_PICK_NUM_UPGRADES,
  UP_DRILL_NUM_UPGRADES,
  UP_CALCULATOR_NUM_UPGRADES,
  UP_FILTER_NUM_UPGRADES,
  UP_CONVEYOR_BELT_NUM_UPGRADES,
  UP_CARGO_NUM_UPGRADES,
  UP_DRILL_IDLE_NUM_UPGRADES,
  UP_DRILL_BEARINGS_NUM_UPGRADES,
  UP_DRILL_NITRO_NUM_UPGRADES,
  UP_MOVE_NUM_UPGRADES,
  UP_ACCOUNTANT_NUM_UPGRADES,
  UP_MANAGER_NUM_UPGRADES,
  UP_BRAIN_NUM_UPGRADES
};

const unsigned long* const UP_COSTS[] PROGMEM = {
  UP_PICK_COST,
  UP_DRILL_COST,
  UP_CALCULATOR_COST,
  UP_FILTER_COST,
  UP_CONVEYOR_BELT_COST,
  UP_CARGO_COST,
  UP_DRILL_IDLE_COST,
  UP_DRILL_BEARINGS_COST,
  UP_DRILL_NITRO_COST,
  UP_MOVE_COST,
  UP_ACCOUNTANT_COST,
  UP_MANAGER_COST,
  UP_BRAIN_COST
};

const unsigned long* const UP_VALUES[] PROGMEM = {
  UP_PICK_VALUE,
  UP_DRILL_VALUE,
  UP_CALCULATOR_VALUE,
  UP_FILTER_VALUE,
  UP_CONVEYOR_BELT_VALUE,
  UP_CARGO_VALUE,
  UP_DRILL_IDLE_VALUE,
  UP_DRILL_BEARINGS_VALUE,
  UP_DRILL_NITRO_VALUE,
  UP_MOVE_VALUE,
  UP_ACCOUNTANT_VALUE,
  UP_MANAGER_VALUE,
  UP_BRAIN_VALUE
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
void upgradeDirtFilter(Game* game, const unsigned long val);
void upgradeConveyorBelt(Game* game, const unsigned long val);
void upgradeCargo(Game* game, const unsigned long val);
void upgradeDrillIdle(Game* game, const unsigned long val);
void upgradeDrillBearings(Game* game, const unsigned long val);
void upgradeDrillNitro(Game* game, const unsigned long val);
void upgradeMove(Game* game, const unsigned long val);
void upgradeAccountant(Game* game, const unsigned long val);
void upgradeManager(Game* game, const unsigned long val);
void upgradeBrain(Game* game, const unsigned long val);

const UpgradeFunctionPtr PROGMEM UP_UPGRADE_FUNCTIONS[] = {
  &upgradePick,
  &upgradeDrill,
  &upgradeCalculator,
  &upgradeDirtFilter,
  &upgradeConveyorBelt,
  &upgradeCargo,
  &upgradeDrillIdle,
  &upgradeDrillBearings,
  &upgradeDrillNitro,
  &upgradeMove,
  &upgradeAccountant,
  &upgradeManager,
  &upgradeBrain,
};

#endif