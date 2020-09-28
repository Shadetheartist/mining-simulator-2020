#include "interface.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "graphics.h"
#include "resources.h"
#include "menu.h"
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define UI_FOOTER_X 0
#define UI_FOOTER_Y 55
#define UI_FOOTER_WIDTH 128
#define UI_FOOTER_HEIGHT 10

#define UI_SIDEBAR_X 64
#define UI_SIDEBAR_Y 0
#define UI_SIDEBAR_WIDTH 64
#define UI_SIDEBAR_HEIGHT 54

Interface::Interface(Game *game)
{
  this->game = game;
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
}

bool Interface::init()
{
  return display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void Interface::abbreviateNumber(const float n, char *buffer, const unsigned char precision)
{
  unsigned char numZeros = floor(log10(n));

  if (numZeros <= 2)
  {
    sprintf(buffer, "%d", (int)n);
    return;
  }

  char c = '\0';

  if (numZeros > 2)
  {
    c = 'K';
  }

  if (numZeros > 5)
  {
    c = 'M';
  }

  if (numZeros > 8)
  {
    c = 'B';
  }

  if (numZeros > 11)
  {
    c = 'T';
  }

  float _n = n / pow(10, floor(numZeros / 3) * 3);

  switch(precision){
    case 0:
      sprintf(buffer, "%d%c", (int)_n, c);
      break;
    
    case 1:
      sprintf(buffer, "%d.%d%c", (int)_n, (int)((_n - (int)_n) * 10), c);
      break;
    
    case 2:
      sprintf(buffer, "%d.%d%c", (int)_n, (int)((_n - (int)_n) * 100), c);
      break;
  }

}

void Interface::drawMenuFooter()
{
  display->fillRect(
      UI_FOOTER_X, UI_FOOTER_Y,
      UI_FOOTER_WIDTH, UI_FOOTER_HEIGHT,
      BLACK);

  display->drawLine(
      UI_FOOTER_X, UI_FOOTER_Y,
      UI_FOOTER_WIDTH, UI_FOOTER_Y,
      WHITE);

  //write text
  display->setTextWrap(false);
  display->setTextSize(1);
  display->setTextColor(WHITE);
  display->setCursor(UI_FOOTER_X, UI_FOOTER_Y + 2);

  display->print('$');
  char buffer[8];
  abbreviateNumber(game->state.money, buffer, 2);
  display->print(buffer);
}

void Interface::drawCargoSidebar()
{
  //draw vertical divider
  display->drawLine(
      UI_SIDEBAR_X, UI_SIDEBAR_Y,
      UI_SIDEBAR_X, UI_SIDEBAR_Y + UI_SIDEBAR_HEIGHT,
      WHITE);

  if (!game->isShowingMenu || game->menuSelectedWindow == 1)
  {
    //draw header area
    display->fillRect(
        UI_SIDEBAR_X, UI_SIDEBAR_Y,
        UI_SIDEBAR_WIDTH, 8,
        WHITE);
  }
  else
  {
    //draw header area
    display->drawLine(
        UI_SIDEBAR_X, UI_SIDEBAR_Y + 8,
        UI_SIDEBAR_X + UI_SIDEBAR_WIDTH, UI_SIDEBAR_Y + 8,
        WHITE);
  }

  //up/down arrows
  display->drawBitmap(128 - G_UP_DOWN_BMP_WIDTH, 2, G_UP_DOWN_BMP, G_UP_DOWN_BMP_WIDTH, G_UP_DOWN_BMP_HEIGHT, INVERSE);

  //write text
  display->setTextSize(1);
  display->setTextColor(INVERSE);
  display->setCursor(UI_SIDEBAR_X + 1, UI_SIDEBAR_Y);

  display->print(F("INV "));
  unsigned int percentCargo = game->getCargoPercentage();
  if (percentCargo < 100)
  {
    display->print(percentCargo);
    display->println('%');
  }
  else
  {
    display->println(F("FULL"));
  }

  display->setTextColor(WHITE);

  char buffer[3];
  unsigned char line = 0;
  for (int i = game->menuWindowOption; i < NUM_RESOURCES; i++)
  {
    int c = (NUM_RESOURCES - 1) - i;

    if (game->state.cargo[c] == 0)
    {
      continue;
    }

    display->setCursor(
        UI_SIDEBAR_X + 2,
        1 + UI_SIDEBAR_Y + (1 + line) * 8);

    line++;

    strcpy_P(buffer, (char *)pgm_read_word(&(RESOURCE_NAMES[c])));

    display->print(buffer);
    display->print(F(" x "));

    char valBuffer[8];
    abbreviateNumber(game->state.cargo[c], valBuffer, 0);
    display->println(valBuffer);
  }
}

void Interface::drawInfoSidebar()
{
  //draw vertical divider
  display->drawLine(
      UI_SIDEBAR_X, UI_SIDEBAR_Y,
      UI_SIDEBAR_X, UI_SIDEBAR_Y + UI_SIDEBAR_HEIGHT,
      WHITE);

  display->setTextWrap(true);
  display->setTextSize(1);
  display->setTextColor(WHITE);

  char buffer[40];

  strcpy_P(buffer, (char *)pgm_read_word(&(MENU_OPTION_INFOS[game->menuSelectedPage + game->menuSelectedOption])));

  //organize help text into lines that fit into the sidebar (10 chars per line, 6 lines max)
  char c = 0;
  unsigned char n = 0;

  for (unsigned char i = 0; i < 6; i++)
  {
    char lineBuffer[11];
    unsigned char o;
    for (o = 0; o < 10; o++)
    {
      c = buffer[n];
      n++;

      if (c == '\n')
      {
        lineBuffer[o] = 0;
        break;
      }

      lineBuffer[o] = c;
      if (c == 0)
      {
        break;
      }
    }

    lineBuffer[min(10, o + 1)] = 0;

    display->setCursor(UI_SIDEBAR_X + 2, i * 8);
    display->println(lineBuffer);

    if (c == 0)
    {
      break;
    }
  }

  int up = getUpgradeFromMenuItem(game->menuSelectedPage + game->menuSelectedOption);

  if (up != -1)
  {
    unsigned long cost = getUpgradeCost(up, game->state.upgrades[up] + 1);
    unsigned char numUpgrades = getNumUpgrades(up);
    unsigned long currentVal = getUpgradeValue(up, game->state.upgrades[up]);
    unsigned long nextVal = getUpgradeValue(up, min(numUpgrades - 1, game->state.upgrades[up] + 1));

    display->setCursor(UI_SIDEBAR_X + 2, 5 * 8);

    if (currentVal == nextVal)
    {
      display->print(F("MAXED"));
    }
    else
    {
      display->print('$');

      char buffer[8];
      abbreviateNumber(cost, buffer, 2);
      display->print(buffer);

      display->setCursor(UI_SIDEBAR_X + 2, 6 * 8);

      abbreviateNumber(currentVal, buffer, 0);
      display->print(buffer);
      display->print(F(" > "));

      abbreviateNumber(nextVal, buffer, 0);
      display->print(buffer);
    }
  }
}

void Interface::drawPick()
{
  unsigned char frame = game->gameboard->triggerBtn.read();

  display->drawBitmap(
      8,
      35,
      G_PICK_FRAMES[frame],
      G_PICK_FRAMES_WIDTH,
      G_PICK_FRAMES_HEIGHT,
      WHITE);
}


void Interface::drawDrill()
{
  unsigned char frame = game->drillFrame;
  if(digitalRead(PIN_TRIGGER) == LOW){
    frame += 2;
  }

  display->drawBitmap(
      8,
      15,
      G_DRILL_MASK_BMP,
      G_DRILL_MASK_WIDTH,
      G_DRILL_MASK_WIDTH,
      BLACK);

  display->drawBitmap(
      8,
      15,
      G_DRILL_FRAMES[frame],
      G_DRILL_FRAMES_WIDTH,
      G_DRILL_FRAMES_HEIGHT,
      WHITE);
}

void Interface::drawMenu()
{
  switch (game->menuSelectedPage + game->menuSelectedOption)
  {
  case MENU_MAIN_OPT_SELL_CARGO:
    drawCargoSidebar();
    break;

  default:
    drawInfoSidebar();
    break;
  }

  //write text
  display->setTextSize(1);
  display->setTextColor(WHITE);
  display->setCursor(0, 0);

  char buffer[11];
  for (int i = game->menuSelectedPage; i < game->menuSelectedPage + MENU_PAGE_SIZE; i++)
  {
    strcpy_P(buffer, (char *)pgm_read_word(&(MENU_OPTION_LABELS[i])));
    display->println(buffer);
  }

  if (game->menuSelectedWindow == 0)
  {
    int y = game->menuSelectedOption * 8;
    display->fillRect(
        0, y,
        126 - UI_SIDEBAR_WIDTH, 8,
        INVERSE);
  }

  drawMenuFooter();
}

void Interface::drawForeground()
{
   display->drawBitmap(
      0,
      UI_FOOTER_Y - G_FOREGROUND_HEIGHT,
      G_FOREGROUND_BMP,
      G_FOREGROUND_WIDTH,
      G_FOREGROUND_HEIGHT,
      WHITE);
}


void Interface::drawLandscape()
{ 
  const uint8_t * bmp = 0;
  uint8_t width = 0, height = 0;

  switch(game->state.currentLocation){
    case 0:
      bmp = G_BACKGROUND_1;
      width = G_BACKGROUND_1_WIDTH;
      height = G_BACKGROUND_1_HEIGHT;
      break;
    case 1:
      bmp = G_BACKGROUND_2;
      width = G_BACKGROUND_2_WIDTH;
      height = G_BACKGROUND_2_HEIGHT;
      break;
    case 2:
      bmp = G_BACKGROUND_3;
      width = G_BACKGROUND_3_WIDTH;
      height = G_BACKGROUND_3_HEIGHT;
      break;
    case 3:
      bmp = G_BACKGROUND_4;
      width = G_BACKGROUND_4_WIDTH;
      height = G_BACKGROUND_4_HEIGHT;
      break;
    case 4:
      bmp = G_BACKGROUND_5;
      width = G_BACKGROUND_5_WIDTH;
      height = G_BACKGROUND_5_HEIGHT;
      break;
  }

   display->drawBitmap(
      0,
      0,
      bmp,
      width,
      height,
      WHITE);
}

void Interface::draw()
{
  display->clearDisplay();

  if (game->isShowingMenu)
  {
    drawMenu();
  }
  else
  {
    drawLandscape();
    drawForeground();
    drawCargoSidebar();
    drawMenuFooter();

    if(game->state.upgrades[UP_DRILL] > 0){
      drawDrill();
    }
    else{
      drawPick();
    }
    
  }

  display->display();
}