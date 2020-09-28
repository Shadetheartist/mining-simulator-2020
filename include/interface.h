#ifndef INTERFACE_H
#define INTERFACE_H

#include <Adafruit_SSD1306.h>
#include "game.h"

class Game;
class Interface {
    public:
        Game *game;
        Adafruit_SSD1306 *display;
       
        Interface(Game*);
        
        bool init();
        void draw();

    private:
        void drawLandscape();
        void drawForeground();
        void drawGameFooter();
        void drawMenuFooter();
        void drawCargoSidebar();
        void drawInfoSidebar();
        void drawMenu();
        void drawPick();
        void drawDrill();
        void abbreviateNumber(const float n, char* buffer, const unsigned char precision);


};

#endif