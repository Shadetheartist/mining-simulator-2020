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

void Game::init()
{
  for(int i = 0; i < NUM_RESOURCES; i++)
  {
    state.cargo[i] = 0;
  }

  for(int i = 0; i < NUM_UPGRADES; i++)
  {
    state.upgrades[i] = 0;
  }
  
  state.filter = 0;
  state.money = 0;
  state.numMinedPerPickUse = 1;
  state.currentLocation = 0;
  state.maxCargo = 25;
  state.cargoSoldPerIteration = 1;
  state.cargoSellDelay = 255;
  state.drillIdle = UP_DRILL_IDLE_INITIAL_VALUE;
  state.drillTempDecrease = UP_DRILL_BEARINGS_INITIAL_VALUE;
  state.drillNitro = UP_DRILL_NITRO_INITIAL_VALUE;
  state.accountants = 0;
  state.managers = UP_MANAGER_INITIAL_VALUE;
  state.numMinedPerDrillUse = 0;

  isShowingMenu = false;
  shouldDraw = true;
  menuSelectedPage = 0;

  menuSelectedWindow = 0;
  menuWindowOption = 0;

  drillTemp = 0;
  maxDrillTemp = 1000;
  drillTempIncrase = 8;
  lastDrillDecreaseMs = 0;
  
  accountantSellMs = 0;

  gameboard->setBlueLED(LOW);
  gameboard->setLowerGreenLED(LOW);
  gameboard->setUpperGreenLED(LOW);
  gameboard->setRedLED(LOW);
  
  interface->init();
}

void Game::save(){
  EEPROM.put(0, state);
}

void Game::load(){
  EEPROM.get(0, state);
}

void Game::accountantPassive(){
  if(state.accountants > 0 && millis() - accountantSellMs > state.managers * 1000){
    accountantSellMs = millis();
    unsigned int totalSold = 0;
    unsigned long sellRemaining = state.accountants;
    for(unsigned char i = 0; i < NUM_RESOURCES; i++){
      
      if(sellRemaining <= 0){
        break;
      }

      unsigned long resourceValue = (unsigned long)pgm_read_dword(&RESOURCE_VALUES[i]);
      unsigned long numSold = min(state.cargo[i], sellRemaining);
      unsigned long value = resourceValue * numSold;
      sellRemaining -= numSold;

      cargoChanged = true;
      state.cargo[i] -= numSold;

      totalSold += value;
    }
    
    addMoney(totalSold);

    if(totalSold > 0){
      gameboard->triggerMoneySound();
    }
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

char Game::mine(unsigned long amount)
{
  if (getCargoPercentage() >= 100)
  {
    return -1;
  }

  unsigned char resource = getRandomResource();

  if(resource < state.filter){
    return -1;
  }

  state.cargo[resource] += amount;

  return resource;
}

void Game::pick()
{
  char bestResource = 0;

  for(unsigned int n = 0; n < state.numMinedPerPickUse; n++){
    char resource = mine(1);
    
    if(resource == -1){
      continue;
    }

    if(resource > bestResource){
      bestResource = resource;
    }
  }
  

  if(bestResource != -1){
    gameboard->triggerPickSound(bestResource);
  }
  
}

void Game::drill()
{
  while(!digitalRead(PIN_BOOST))
  {
    accountantPassive();

    drillFrame++;
    if(drillFrame > 2){
      drillFrame = 1;
    }

    char bestResource = 0;
    float heatPercentage = drillTemp / maxDrillTemp;
  
    unsigned char nitro = 1;
    if(heatPercentage > 0.9){
      nitro = state.drillNitro;
    }
    
    char resource = mine(state.numMinedPerDrillUse * nitro);
    if(resource != -1){

    }

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

    gameboard->triggerDrillSound(bestResource);
    interface->draw();

    unsigned long waitMillis = millis() + (state.drillIdle - (heatPercentage * state.drillIdle));
    while(millis() < waitMillis){
      gameboard->boostBtn.update();
      if(gameboard->boostBtn.rose()){
        return;
      }

      unsigned char rpm = 2;
      if(!digitalRead(PIN_TRIGGER)){
        rpm = 3;
      }

      gameboard->triggerClickSound();
      float d = (state.drillIdle - (heatPercentage * state.drillIdle)) / rpm;
      if(d > 0){
        delay(d);
      }
      else{
        delayMicroseconds(d * 1000);
      }
    }
  }

  drillFrame = 0;
  shouldDraw = true;
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
  
  float percentCargoFullness = 0;
  for (int i = 0; i < NUM_RESOURCES; i++)
  {
    percentCargoFullness += state.cargo[i];
  }

  lastCargoPercentage = ((percentCargoFullness / state.maxCargo) * 100);
  return lastCargoPercentage;
}


void Game::showMenu()
{
  menuSelectedOption = 0;
  isShowingMenu = true;
  shouldDraw = true;
  gameboard->triggerMeepSound();
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
  gameboard->dpadLeftBtn.update();
  gameboard->dpadRightBtn.update();
  gameboard->dpadMiddleBtn.update();

  if (gameboard->triggerBtn.fell())
  {
    isShowingMenu = false;
    menuSelectedWindow = 0;

    //remove these if you dont want menu reset
    menuWindowOption = 0;
    menuSelectedPage = 0;

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
    case MENU_BUY2_OPT_FILTER:
    case MENU_UPGRADE_DRILL_OPT_IDLE:
    case MENU_UPGRADE_DRILL_OPT_BEARINGS:
    case MENU_UPGRADE_DRILL_OPT_NITRO:
    case MENU_MAIN_OPT_MOVE:
    case MENU_HIRE_OPT_ACCOUNTANT:
    case MENU_HIRE_OPT_MANAGER:
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
    if (menuSelectedWindow == 0)
    {
      if (menuSelectedOption == 0)
      {
        menuSelectedOption = MENU_PAGE_SIZE - 1;
      }
      else
      {
        menuSelectedOption--;
      }
    }
    else
    {
      if (menuWindowOption > 0)
      {
        menuWindowOption--;
      }
    }

    gameboard->triggerMeepSound();
    shouldDraw = true;
  }

  if (gameboard->dpadDownBtn.fell())
  {
    if (menuSelectedWindow == 0)
    {
      menuSelectedOption++;

      //loop to top
      if (menuSelectedOption >= MENU_PAGE_SIZE)
      {
        menuSelectedOption = 0;
      }
    }
    else
    {
      if (menuWindowOption < 0xff)
      {
        menuWindowOption++;
      }
    }

    gameboard->triggerMeepSound();
    shouldDraw = true;
  }

  if (menuSelectedWindow == 0 && gameboard->dpadRightBtn.fell())
  {
    menuSelectedWindow = 1;
    menuWindowOption = 0;
    gameboard->triggerMeepSound();
    shouldDraw = true;
  }

  if (menuSelectedWindow == 1 && gameboard->dpadLeftBtn.fell())
  {
    menuSelectedWindow = 0;
    menuWindowOption = 0;
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
  }

  if (gameboard->triggerBtn.fell())
  {
    interface->draw();
    pick();
    shouldDraw = false;
  }
  else if (gameboard->triggerBtn.rose())
  {
    shouldDraw = true;
  }

  if (gameboard->dpadMiddleBtn.fell())
  {
    showMenu();
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
