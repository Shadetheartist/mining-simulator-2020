#include "game.h"
#include "interface.h"
#include "gameboard.h"
#include "resources.h"
#include "menu.h"
#include <EEPROM.h>

void (*resetFunc)(void) = 0;

bool Game::shouldDraw = true;

Game::Game()
{
  interface = new Interface(this);
  gameboard = new Gameboard();
}

void initState(Game* game){
  game->state.charm = UP_CHARM_INITIAL_VALUE;
  game->state.money = 1000;
  game->state.numMinedPerPickUse = UP_PICK_INITIAL_VALUE;
  game->state.currentLocation = 0;
  game->state.maxCargo = UP_CARGO_INITIAL_VALUE;
  game->state.cargoSoldPerIteration = UP_CONVEYOR_BELT_INITIAL_VALUE;
  game->state.cargoSellDelay = UP_CALCULATOR_INITIAL_VALUE;
  game->state.drillIdle = UP_DRILL_IDLE_INITIAL_VALUE;
  game->state.drillTempDecrease = UP_DRILL_BEARINGS_INITIAL_VALUE;
  game->state.drillNitro = UP_DRILL_NITRO_INITIAL_VALUE;
  game->state.accountants = 0;
  game->state.managers = UP_MANAGER_INITIAL_VALUE;
  game->state.numMinedPerDrillUse = UP_DRILL_INITIAL_VALUE;
  game->state.brain = UP_BRAIN_INITIAL_VALUE;
  game->state.dumper = UP_DUMPER_INITIAL_VALUE;

  for(int i = 0; i < NUM_RESOURCES; i++)
  {
    game->state.cargo[i] = 0;
  }

  for(int i = 0; i < NUM_UPGRADES; i++)
  {
    game->state.upgrades[i] = 0;
  }

}

void initDynamics(Game* game){
  game->isShowingMenu = false;
  game->shouldDraw = true;
  game->menuSelectedPage = 0;
  game->menuSelectedOption = 0;
  game->drillFrame = 0;
  game->drillTemp = 0;
  game->maxDrillTemp = 1000;
  game->drillTempIncrase = 12;
  game->lastDrillDecreaseMs = 0;
  game->accountantSellMs = 0;
  game->cargoChanged = true;
  game->lastCargoPercentage = 0;
  game->accountantSellMs = 0;
  game->dumperDumpMs = 0;

  game->gameboard->setBlueLED(LOW);
  game->gameboard->setLowerGreenLED(LOW);
  game->gameboard->setUpperGreenLED(LOW);
  game->gameboard->setRedLED(LOW);
  game->gameboard->mute = false;

}


void Game::init()
{
  initState(this);
  initDynamics(this);
  interface->init();
}

void Game::save(){
  EEPROM.put(0, state);
}

void Game::load(){
  EEPROM.get(0, state);
  initDynamics(this);
}

void Game::accountantPassive(){
  if(state.accountants > 0 && millis() - accountantSellMs > state.managers + state.cargoSellDelay * 100){
    
    accountantSellMs = millis();
    unsigned int totalSold = 0;
    unsigned long sellRemaining = state.accountants + state.cargoSoldPerIteration * 4;
    for(unsigned char i = NUM_RESOURCES-1; i > 0; i--){
      
      if(sellRemaining <= 0){
        break;
      }

      unsigned long resourceValue = (unsigned long)pgm_read_dword(&RESOURCE_VALUES[i]);
      unsigned long numSold = min(state.cargo[i], sellRemaining);
      unsigned long value = resourceValue * numSold;
      sellRemaining -= numSold;
     
      state.cargo[i] -= numSold;

      totalSold += value;
    }
    
    addMoney(totalSold);

    if(totalSold > 0){
      gameboard->triggerMoneySound();
      cargoChanged = true;
    }
  }
}


void Game::dumperPassive(){
  if(state.dumper > 0 && state.cargo[0] > 0 && millis() - dumperDumpMs > state.managers){
    dumperDumpMs = millis();
    unsigned long amountToDump = state.dumper + state.cargoSoldPerIteration * 10;
    state.cargo[0] = max(0, state.cargo[0] - amountToDump);
    cargoChanged = true;
    shouldDraw = true;
    gameboard->triggerDumpSound();
  }
}

void Game::drillPassive(){
  if(state.upgrades[UP_DRILL] == 0){
    return;
  }

  if(digitalRead(PIN_TRIGGER) && drillTemp > 0 && millis() - lastDrillDecreaseMs > 100){
    lastDrillDecreaseMs = millis();
    if(drillTemp > state.drillTempDecrease){
      drillTemp -= state.drillTempDecrease;
    }else{
      drillTemp = 0;
    }
  }

  float heatPercentage = drillTemp / maxDrillTemp;

  gameboard->setBlueLED(heatPercentage < 0.01);
  gameboard->setLowerGreenLED(heatPercentage >= 0.01);
  gameboard->setUpperGreenLED(heatPercentage > 0.50);
  gameboard->setRedLED(heatPercentage > 0.9);
}


char Game::getRandomResource(){

  unsigned long r = random(0, 1000000);
  
  // charms grant additional tries for a better result
  for(char i = 0; i < state.charm; i++){
    unsigned long charm_r = random(0, 1000000);

    if(charm_r > r){
      r = charm_r;
    }
  }

  unsigned long c = 0;

  for (int i = 0; i < NUM_RESOURCES; i++)
  {
    c += pgm_read_dword_near(&(LOCATION_RESOURCE_RARITIES[state.currentLocation][i]));

    if (r < c)
    {
      return i;
    }
  }

  return -1;
}


void Game::drillIdleSound()
{
  float heatPercentage = drillTemp / maxDrillTemp;
  
  if(digitalRead(PIN_BOOST) && heatPercentage < 0.01){
    return;
  }

  if(!digitalRead(PIN_TRIGGER) && digitalRead(PIN_BOOST)){
    return;
  }
  
  unsigned char rpm = 2;
  if(!digitalRead(PIN_TRIGGER) && !digitalRead(PIN_BOOST)){
    rpm = 3;
  }


  float ms = (state.drillIdle - (heatPercentage * state.drillIdle)) / rpm;
  ms = min(ms, 250);

  if(micros() - lastDrillIdleUs > ms * 1000){
    lastDrillIdleUs = micros();
    gameboard->triggerClickSound();
  }
}


char Game::mine(unsigned long amount)
{
  unsigned long remainingSpace = state.maxCargo - getTotalCargo();

  if(remainingSpace == 0){
    return -1;
  }
  
  unsigned char resource = getRandomResource();

  state.cargo[resource] += min(remainingSpace, amount);
  cargoChanged = true;

  return resource;
}

void Game::pick()
{
  char resource = mine(state.numMinedPerPickUse);
   
  if(resource >= 0){
    gameboard->triggerPickSound(resource);
    return;
  } else if(resource == -1){
    gameboard->triggerBadSound();
    return;
  }
}

void Game::drill()
{
  while(!digitalRead(PIN_BOOST))
  {
    accountantPassive();
    dumperPassive();

    drillFrame++;
    if(drillFrame > 2){
      drillFrame = 1;
    }

    float heatPercentage = drillTemp / maxDrillTemp;
  
    unsigned char nitro = 1;
    if(heatPercentage > 0.9){
      nitro = state.drillNitro;
    }
    
    char resource = mine(state.numMinedPerDrillUse * nitro + state.numMinedPerPickUse);
    
    if(digitalRead(PIN_TRIGGER) == LOW){
      drillTemp += drillTempIncrase;
      
      //drill broke, should be temporarily out of service
      //setting the temp to 0 means the user has to start from a filly cold drill
      if(drillTemp > maxDrillTemp){
        drillTemp = 1;
        drillPassive();
        return;
      }
    }
    
    drillPassive();

    if(resource >= 0){
      gameboard->triggerDrillSound(resource);
    }

    interface->draw();
    unsigned long totalIdle = state.drillIdle + state.brain / 10;
    unsigned long waitMillis = millis() + (totalIdle - (heatPercentage * totalIdle));
    while(millis() < waitMillis){
      gameboard->boostBtn.update();
      if(gameboard->boostBtn.rose()){
        return;
      }
      drillIdleSound();
    }
  }

}

void Game::upgrade(unsigned char up)
{
  unsigned char currentUpgrade = state.upgrades[up];

  //get the size of the upgrade array for this upgrade
  unsigned char numUpgrades = getNumUpgrades(up);

  //dont upgrade if we're maxed out
  if (currentUpgrade + 1 >= numUpgrades)
  {
    return;
  }

  unsigned long cost = getUpgradeCost(up, currentUpgrade + 1);
  unsigned long val = getUpgradeValue(up, currentUpgrade + 1);

  //UPGRADE!
  if (state.money >= cost)
  {
    //this calls a predefined function from upgrades.cpp
    UpgradeFunctionPtr upgradeFunction = getUpgradeFn(up);
    (*upgradeFunction)(this, val);
    
    state.upgrades[up]++;
    state.money -= cost;
    gameboard->triggerSpendSound();
  }
}

unsigned long Game::getCargoPercentage()
{
  if(cargoChanged == false){
    return lastCargoPercentage;
  }
  
  lastCargoPercentage = round(((getTotalCargo() / state.maxCargo) * 100));
  
  return lastCargoPercentage;
}

float Game::getTotalCargo()
{
  float totalCargo = 0;

  for (int i = 0; i < NUM_RESOURCES; i++)
  {
    totalCargo += state.cargo[i];
  }

  return totalCargo;
}

void Game::sellCargo()
{
  //have to use the raw digital reads for this case otherwise it always double proccs
  while (digitalRead(PIN_DPAD_MIDDLE) == LOW)
  {
    unsigned char i;
    for (i = NUM_RESOURCES - 1; i > 0; i--)
    {
      if (state.cargo[i] > 0)
      {
        break;
      }
    }

    unsigned long resourceValue = (unsigned long)pgm_read_dword(&RESOURCE_VALUES[i]);
    unsigned long numSold = min(state.cargo[i], state.cargoSoldPerIteration);
    unsigned long value = resourceValue * numSold;

    cargoChanged = true;
    state.cargo[i] -= numSold;

    if(value > 0){
      addMoney(value);
      gameboard->triggerMoneySound();
    }

    interface->draw();
    delay(state.cargoSellDelay);
  }
}

void Game::menuUpdate()
{
  gameboard->triggerBtn.update();
  gameboard->dpadUpBtn.update();
  gameboard->dpadDownBtn.update();
  gameboard->dpadMiddleBtn.update();

  if (gameboard->triggerBtn.fell())
  {
    isShowingMenu = false;
    menuSelectedPage = 0;
    menuSelectedOption = 0;

    return;
  }

  bool meep = true;

  if (gameboard->dpadMiddleBtn.fell())
  {
    switch (menuSelectedPage + menuSelectedOption)
    {
    case MENU_MAIN_OPT_SELL_CARGO:
      sellCargo();
      meep = false;
      break;

    case MENU_MAIN_OPT_SHOP:
      menuSelectedPage = MENU_SHOP_PAGE;
      menuSelectedOption = 0;
      break;

    case MENU_MAIN_OPT_RESTART:
      resetFunc();
      break;

    case MENU_SHOP_OPT_BACK:
      menuSelectedPage = MENU_MAIN_PAGE;
      menuSelectedOption = MENU_MAIN_OPT_SHOP - MENU_MAIN_PAGE;
      break;

    case MENU_SHOP_OPT_BUY:
      menuSelectedPage = MENU_BUY_PAGE;
      menuSelectedOption = 0;
      break;

    case MENU_BUY_OPT_BACK:
      menuSelectedPage = MENU_SHOP_PAGE;
      menuSelectedOption = MENU_SHOP_OPT_BUY - MENU_SHOP_PAGE;
      break;

    case MENU_SHOP_OPT_BUY2:
      menuSelectedPage = MENU_BUY2_PAGE;
      menuSelectedOption = 0;
      break;

    case MENU_BUY2_OPT_BACK:
      menuSelectedPage = MENU_SHOP_PAGE;
      menuSelectedOption = MENU_SHOP_OPT_BUY2 - MENU_SHOP_PAGE;
      break;

    case MENU_SHOP_OPT_UPGRADE_DRILL:
      menuSelectedPage = MENU_UPGRADE_DRILL_PAGE;
      menuSelectedOption = 0;
      break;
    
    case MENU_UPGRADE_DRILL_OPT_BACK:
      menuSelectedPage = MENU_SHOP_PAGE;
      menuSelectedOption = MENU_SHOP_OPT_UPGRADE_DRILL - MENU_SHOP_PAGE;
      break;

    case MENU_SHOP_OPT_HIRE:
      menuSelectedPage = MENU_HIRE_PAGE;
      menuSelectedOption = 0;
      break;
    
    case MENU_HIRE_OPT_BACK:
      menuSelectedPage = MENU_SHOP_PAGE;
      menuSelectedOption = MENU_SHOP_OPT_HIRE - MENU_SHOP_PAGE;
      break;

    case MENU_MAIN_OPT_OPTIONS:
      menuSelectedPage = MENU_OPTIONS_PAGE;
      menuSelectedOption = 0;
      break;
    
    case MENU_OPTIONS_OPT_BACK:
      menuSelectedPage = MENU_MAIN_PAGE;
      menuSelectedOption = MENU_MAIN_OPT_OPTIONS - MENU_MAIN_PAGE;
      break;

    case MENU_OPTIONS_OPT_MUTE:
      gameboard->mute = !gameboard->mute;
      break;

    case MENU_MAIN_OPT_SAVE:
    case MENU_OPTIONS_OPT_SAVE:
      save();
      break;

    case MENU_OPTIONS_OPT_LOAD:
      load();
      break;

    case MENU_BUY_OPT_PICK:
    case MENU_BUY_OPT_CALCULATOR:
    case MENU_BUY_OPT_CARGO:
    case MENU_BUY_OPT_CONVEYOR_BELT:
    case MENU_BUY2_OPT_DRILL:
    case MENU_BUY2_OPT_CHARM:
    case MENU_UPGRADE_DRILL_OPT_IDLE:
    case MENU_UPGRADE_DRILL_OPT_BEARINGS:
    case MENU_UPGRADE_DRILL_OPT_NITRO:
    case MENU_MAIN_OPT_MOVE:
    case MENU_HIRE_OPT_ACCOUNTANT:
    case MENU_HIRE_OPT_MANAGER:
    case MENU_HIRE_OPT_DUMPER:
    case MENU_BUY_OPT_BRAIN_STEM:
      char up = getUpgradeFromMenuItem(menuSelectedPage + menuSelectedOption);
      upgrade(up);
      break;
    }

    shouldDraw = true;

    if (meep)
    {
      gameboard->triggerMeepSound();
    }
  }

  if (gameboard->dpadUpBtn.fell())
  {
    if (menuSelectedOption == 0)
    {
      menuSelectedOption = MENU_PAGE_SIZE - 1;
    }
    else
    {
      menuSelectedOption--;
    }

    gameboard->triggerMeepSound();
    shouldDraw = true;
  }

  if (gameboard->dpadDownBtn.fell())
  {
    menuSelectedOption++;

    //loop to top
    if (menuSelectedOption >= MENU_PAGE_SIZE)
    {
      menuSelectedOption = 0;
    }

    gameboard->triggerMeepSound();
    shouldDraw = true;
  }

  if (shouldDraw)
  {
    interface->draw();
    shouldDraw = false;
  }
}


void Game::update()
{
  drillPassive();
  accountantPassive();
  dumperPassive();
  
  if(state.upgrades[UP_DRILL] > 0){
    drillIdleSound();
  } else if(state.brain != 0){
    if(digitalRead(PIN_TRIGGER) && digitalRead(PIN_BOOST) && millis() - lastBrainPickMs > state.brain && getCargoPercentage() < 100){
      lastBrainPickMs = millis();

      pickFrame = 1;

      if(isShowingMenu == false){
        interface->draw();
      }

      pick();
      pickFrame = 0;

      shouldDraw = true;
     
    }
  }

  if (isShowingMenu)
  {
    menuUpdate();
    return;
  }

  gameboard->boostBtn.update();
  gameboard->triggerBtn.update();
  gameboard->dpadMiddleBtn.update();

  if (state.upgrades[UP_DRILL] > 0 && gameboard->boostBtn.fell())
  {
    drill();
    drillFrame = 0;
    shouldDraw = true;
  }

  if (gameboard->triggerBtn.fell())
  {
    interface->draw();
    pick();
    lastBrainPickMs = millis();
    shouldDraw = false;
  }
  else if (gameboard->triggerBtn.rose())
  {
    shouldDraw = true;
  }

  if (gameboard->dpadMiddleBtn.fell())
  {
    menuSelectedOption = 0;
    isShowingMenu = true;
    shouldDraw = true;
    gameboard->triggerMeepSound();
  }


  if (shouldDraw)
  {
    interface->draw();
    shouldDraw = false;
  }
}

void Game::addMoney(const unsigned long amount)
{
  if(amount > 0){
    state.money += amount;
    shouldDraw = true;
  }
}
