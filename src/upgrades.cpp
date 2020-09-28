#include "upgrades.h"
#include "game.h"
#include "menu.h"

int getUpgradeFromMenuItem(unsigned char menuItem){
  int up = -1;

  switch (menuItem)
  {
    case MENU_BUY_OPT_PICK:
      up = UP_PICK;
      break;
    case MENU_BUY_OPT_CALCULATOR:
      up = UP_CALCULATOR;
      break;
    case MENU_BUY_OPT_CARGO:
      up = UP_CARGO;
      break;
    case MENU_BUY2_OPT_DRILL:
      up = UP_DRILL;
      break;
    case MENU_BUY_OPT_CONVEYOR_BELT:
      up = UP_CONVEYOR_BELT;
      break;
    case MENU_BUY2_OPT_FILTER:
      up = UP_FILTER;
      break;
    case MENU_UPGRADE_DRILL_OPT_IDLE:
      up = UP_DRILL_IDLE;
      break;
    case MENU_UPGRADE_DRILL_OPT_BEARINGS:
      up = UP_DRILL_BEARINGS;
      break;
    case MENU_UPGRADE_DRILL_OPT_NITRO:
      up = UP_DRILL_NITRO;
      break;
    case MENU_MAIN_OPT_MOVE:
      up = UP_MOVE;
      break;
    case MENU_HIRE_OPT_ACCOUNTANT:
      up = UP_ACCOUNTANT;
      break;
    case MENU_HIRE_OPT_MANAGER:
      up = UP_MANAGER;
      break;
  }

  return up;
}

void upgradePick(Game *game, const unsigned long val)
{
  game->state.numMinedPerPickUse = val;
}

void upgradeDrill(Game *game, const unsigned long val) {
  game->state.numMinedPerDrillUse = val;
}

void upgradeCalculator(Game *game, const unsigned long val)
{
  game->state.cargoSellDelay = val;
}

void upgradeDirtFilter(Game *game, const unsigned long val) 
{
  game->state.filter = val;
}

void upgradeConveyorBelt(Game *game, const unsigned long val) 
{
  game->state.cargoSoldPerIteration = val;
}

void upgradeCargo(Game *game, const unsigned long val)
{
  game->state.maxCargo = val;
}

void upgradeDrillIdle(Game* game, const unsigned long val){
  game->state.drillIdle = val;
}

void upgradeDrillBearings(Game* game, const unsigned long val){
  game->state.drillTempDecrease = val;
}

void upgradeDrillNitro(Game* game, const unsigned long val){
  game->state.drillNitro = val;
}

void upgradeMove(Game* game, const unsigned long val){
  game->state.currentLocation = val;
}

void upgradeAccountant(Game* game, const unsigned long val){
  game->state.accountants = val;
}

void upgradeManager(Game* game, const unsigned long val){
  game->state.managers = val;
}

unsigned char getNumUpgrades(unsigned char up){
  //get the size of the upgrade array for this upgrade
  return (unsigned char)pgm_read_byte(&(NUM_UPGRADES_TABLE[up]));
}

unsigned long getUpgradeCost(unsigned char up, unsigned char level){
  unsigned long *costs = (unsigned long *)pgm_read_word(&UP_COSTS[up]);
  return pgm_read_dword(&costs[level]);
}

unsigned long getUpgradeValue(unsigned char up, unsigned char level){
  unsigned long *vals = (unsigned long *)pgm_read_word(&UP_VALUES[up]);
  return pgm_read_dword(&vals[level]);
}

UpgradeFunctionPtr getUpgradeFn(unsigned char up){
  return (UpgradeFunctionPtr)pgm_read_word(&(UP_UPGRADE_FUNCTIONS[up]));
}
