#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "upgrades.h"

#define MENU_PAGE_SIZE 6

#define MENU_MAIN_PAGE                  (0 * MENU_PAGE_SIZE)
#define MENU_SHOP_PAGE                  (1 * MENU_PAGE_SIZE)
#define MENU_BUY_PAGE                   (2 * MENU_PAGE_SIZE)
#define MENU_BUY2_PAGE                  (3 * MENU_PAGE_SIZE)
#define MENU_UPGRADE_DRILL_PAGE         (4 * MENU_PAGE_SIZE)
#define MENU_HIRE_PAGE                  (5 * MENU_PAGE_SIZE)
#define MENU_OPTIONS_PAGE               (6 * MENU_PAGE_SIZE)

#define MENU_MAIN_OPT_SELL_CARGO        (MENU_MAIN_PAGE + 0)
#define MENU_MAIN_OPT_SHOP              (MENU_MAIN_PAGE + 1)
#define MENU_MAIN_OPT_MOVE              (MENU_MAIN_PAGE + 2)
#define MENU_MAIN_OPT_OPTIONS           (MENU_MAIN_PAGE + 3)
#define MENU_MAIN_OPT_SAVE              (MENU_MAIN_PAGE + 4)
#define MENU_MAIN_OPT_RESTART           (MENU_MAIN_PAGE + 5)
  
#define MENU_SHOP_OPT_BACK              (MENU_SHOP_PAGE + 0)
#define MENU_SHOP_OPT_BUY               (MENU_SHOP_PAGE + 1)
#define MENU_SHOP_OPT_BUY2              (MENU_SHOP_PAGE + 2)
#define MENU_SHOP_OPT_UPGRADE_DRILL     (MENU_SHOP_PAGE + 3)
#define MENU_SHOP_OPT_HIRE              (MENU_SHOP_PAGE + 4)
  
#define MENU_BUY_OPT_BACK               (MENU_BUY_PAGE + 0)
#define MENU_BUY_OPT_PICK               (MENU_BUY_PAGE + 1)
#define MENU_BUY_OPT_CARGO              (MENU_BUY_PAGE + 2)
#define MENU_BUY_OPT_BRAIN_STEM         (MENU_BUY_PAGE + 3)
#define MENU_BUY_OPT_CALCULATOR         (MENU_BUY_PAGE + 4)
#define MENU_BUY_OPT_CONVEYOR_BELT      (MENU_BUY_PAGE + 5)
  
#define MENU_BUY2_OPT_BACK              (MENU_BUY2_PAGE + 0)
#define MENU_BUY2_OPT_DRILL             (MENU_BUY2_PAGE + 1)
#define MENU_BUY2_OPT_FILTER            (MENU_BUY2_PAGE + 2)

#define MENU_UPGRADE_DRILL_OPT_BACK     (MENU_UPGRADE_DRILL_PAGE + 0)
#define MENU_UPGRADE_DRILL_OPT_IDLE     (MENU_UPGRADE_DRILL_PAGE + 1)
#define MENU_UPGRADE_DRILL_OPT_BEARINGS (MENU_UPGRADE_DRILL_PAGE + 2)
#define MENU_UPGRADE_DRILL_OPT_NITRO    (MENU_UPGRADE_DRILL_PAGE + 3)

#define MENU_HIRE_OPT_BACK              (MENU_HIRE_PAGE + 0)
#define MENU_HIRE_OPT_ACCOUNTANT        (MENU_HIRE_PAGE + 1)
#define MENU_HIRE_OPT_MANAGER           (MENU_HIRE_PAGE + 2)

#define MENU_OPTIONS_OPT_BACK           (MENU_OPTIONS_PAGE + 0)
#define MENU_OPTIONS_OPT_MUTE           (MENU_OPTIONS_PAGE + 1)
#define MENU_OPTIONS_OPT_SAVE           (MENU_OPTIONS_PAGE + 2)
#define MENU_OPTIONS_OPT_LOAD           (MENU_OPTIONS_PAGE + 3)

const char MENU_NULL_LABEL[] PROGMEM =          "";
const char MENU_BACK_LABEL[] PROGMEM =          "Back";
const char MENU_SELL_CARGO_LABEL[] PROGMEM =    "Sell Cargo";
const char MENU_SHOP_LABEL[] PROGMEM =          "Shop";
const char MENU_MOVE_LABEL[] PROGMEM =          "Move";
const char MENU_RESTART_LABEL[] PROGMEM =       "Restart";
const char MENU_BUY_LABEL[] PROGMEM =           "Buy";
const char MENU_BUY2_LABEL[] PROGMEM =          "Buy+";
const char MENU_HIRE_LABEL[] PROGMEM =          "Hire";
const char MENU_DRILL_LABEL[] PROGMEM =         "Drill";
const char MENU_CALCULATOR_LABEL[] PROGMEM =    "Calculator";
const char MENU_FILTER_LABEL[] PROGMEM =        "Filter";
const char MENU_CONVEYOR_BELT_LABEL[] PROGMEM = "Conveyor";
const char MENU_PICK_LABEL[] PROGMEM =          "Pick";
const char MENU_CARGO_LABEL[] PROGMEM =         "Cargo";
const char MENU_IDLE_LABEL[] PROGMEM =          "Idle";
const char MENU_BEARINGS_LABEL[] PROGMEM =      "Bearings";
const char MENU_NITRO_LABEL[] PROGMEM =         "Nitro";
const char MENU_UPGRADE_DRILL_LABEL[] PROGMEM = "Up Drill";
const char MENU_ACCOUNTANT_LABEL[] PROGMEM =    "Accountant";
const char MENU_MANAGER_LABEL[] PROGMEM =       "Manager";
const char MENU_OPTIONS_LABEL[] PROGMEM =       "Options";
const char MENU_MUTE_LABEL[] PROGMEM =          "(un)Mute";
const char MENU_SAVE_LABEL[] PROGMEM =          "Save";
const char MENU_LOAD_LABEL[] PROGMEM =          "Load";
const char MENU_BRAIN_STEM_LABEL[] PROGMEM =    "Brain Stem";


const char MENU_HIRE_INFO[] PROGMEM =                 "Hire \nworkers tohelp out";
const char MENU_SHOP_INFO[] PROGMEM =                 "Buy and\nupgrade\nyour items";
const char MENU_UPGRADE_DRILL_INFO[] PROGMEM =        "Upgrade\nyour drill";
const char MENU_MOVE_INFO[] PROGMEM =                 "Move to a\nlocation\nwith rarermaterials";
const char MENU_RESTART_INFO[] PROGMEM =              "Restart\n(doesn't\naffect\nsave)";

const char MENU_BUY_INFO[] PROGMEM =                  "Buy and\nupgrade\nyour tools";
const char MENU_BUY_DRILL_INFO[] PROGMEM =            "New tool!\nDRILL.";
const char MENU_BUY_CALCULATOR_INFO[] PROGMEM =       "Sell cargofaster";
const char MENU_BUY_FILTER_INFO[] PROGMEM =           "Trash no\nlonger\nenters\ninventory";
const char MENU_BUY_CONVEYOR_BELT_INFO[] PROGMEM =    "Move more\ncargo per\nsale";
const char MENU_BUY_CARGO_INFO[] PROGMEM =            "Increase\ncargo\nsize";
const char MENU_BUY_PICK_INFO[] PROGMEM =             "Increase\nore pickedper use";
const char MENU_BUY_IDLE_INFO[] PROGMEM =             "Idle speedincrease";
const char MENU_BUY_BEARINGS_INFO[] PROGMEM =         "Drill\nstays fastfor longer";
const char MENU_BUY_NITRO_INFO[] PROGMEM =            "Redlining\nthe drill\nmultipliesyield";
const char MENU_BUY_BRAIN_STEM_INFO[] PROGMEM =       "Mine\nwithout\nclicking\n(slowly)";

const char MENU_HIRE_ACCOUNTANT_INFO[] PROGMEM =      "Sells\nx of worstcargo\nper y sec";
const char MENU_HIRE_MANAGER_INFO[] PROGMEM =         "Increases\nrate of\naccountantsales";

const char MENU_OPTIONS_INFO[] PROGMEM =              "Mute &\nSave\\Load";
const char MENU_MUTE_INFO[] PROGMEM =                 "Mutes all\nSound";
const char MENU_SAVE_INFO[] PROGMEM =                 "Saves\ngame thru\npower loss";
const char MENU_LOAD_INFO[] PROGMEM =                 "Load savedgame";

const char *const MENU_OPTION_LABELS[] PROGMEM = {
  //MAIN MENU
  MENU_SELL_CARGO_LABEL,
  MENU_SHOP_LABEL,
  MENU_MOVE_LABEL,
  MENU_OPTIONS_LABEL,
  MENU_SAVE_LABEL,
  MENU_RESTART_LABEL,

  //SHOP MENU
  MENU_BACK_LABEL,
  MENU_BUY_LABEL,
  MENU_BUY2_LABEL,
  MENU_UPGRADE_DRILL_LABEL,
  MENU_HIRE_LABEL,
  MENU_NULL_LABEL,

  //BUY MENU 1
  MENU_BACK_LABEL,
  MENU_PICK_LABEL,
  MENU_CARGO_LABEL,
  MENU_BRAIN_STEM_LABEL,
  MENU_CALCULATOR_LABEL,
  MENU_CONVEYOR_BELT_LABEL,

  //BUY MENU 2
  MENU_BACK_LABEL,
  MENU_DRILL_LABEL,
  MENU_FILTER_LABEL,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,

  //UPGRADE DRILL MENU
  MENU_BACK_LABEL,
  MENU_IDLE_LABEL,
  MENU_BEARINGS_LABEL,
  MENU_NITRO_LABEL,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,

  //HIRE MENU
  MENU_BACK_LABEL,
  MENU_ACCOUNTANT_LABEL,
  MENU_MANAGER_LABEL,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,

  //OPTIONS MENU
  MENU_BACK_LABEL,
  MENU_MUTE_LABEL,
  MENU_SAVE_LABEL,
  MENU_LOAD_LABEL,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,

};

const char *const MENU_OPTION_INFOS[] PROGMEM = {
  //MAIN MENU
  MENU_NULL_LABEL,
  MENU_SHOP_INFO,
  MENU_MOVE_INFO,
  MENU_OPTIONS_INFO,
  MENU_SAVE_INFO,
  MENU_RESTART_INFO,

  //SHOP MENU
  MENU_NULL_LABEL,
  MENU_BUY_INFO,
  MENU_BUY_INFO,
  MENU_UPGRADE_DRILL_INFO,
  MENU_HIRE_INFO,
  MENU_NULL_LABEL,

  //BUY MENU 1
  MENU_NULL_LABEL,
  MENU_BUY_PICK_INFO,
  MENU_BUY_CARGO_INFO,
  MENU_BUY_BRAIN_STEM_INFO,
  MENU_BUY_CALCULATOR_INFO,
  MENU_BUY_CONVEYOR_BELT_INFO,

  //BUY MENU 2
  MENU_NULL_LABEL,
  MENU_BUY_DRILL_INFO,
  MENU_BUY_FILTER_INFO,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,

  //UPGRADE DRILL MENU
  MENU_NULL_LABEL,
  MENU_BUY_IDLE_INFO,
  MENU_BUY_BEARINGS_INFO,
  MENU_BUY_NITRO_INFO,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,

  //HIRE MENU
  MENU_NULL_LABEL,
  MENU_HIRE_ACCOUNTANT_INFO,
  MENU_HIRE_MANAGER_INFO,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,
  
  //OPTIONS MENU
  MENU_NULL_LABEL,
  MENU_MUTE_INFO,
  MENU_SAVE_INFO,
  MENU_LOAD_INFO,
  MENU_NULL_LABEL,
  MENU_NULL_LABEL,

};

#endif