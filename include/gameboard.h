#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <Bounce2.h>

#define DEBOUNCE_MS 2

#define PIN_DPAD_UP 6
#define PIN_DPAD_DOWN 10
#define PIN_DPAD_MIDDLE 8
#define PIN_BOOST A0
#define PIN_TRIGGER 2

#define PIN_LED_RED 5
#define PIN_LED_GREEN_1 4
#define PIN_LED_GREEN_2 3
#define PIN_LED_BLUE 11
#define PIN_CLICKER 12

class Gameboard {
    public:       
        bool mute;
        
        Bounce triggerBtn;
        Bounce dpadUpBtn;
        Bounce dpadDownBtn;
        Bounce dpadMiddleBtn;
        Bounce boostBtn;
        
        Gameboard();

        void triggerDrillSound(char);
        void triggerPickSound(char);
        void triggerClickSound();
        void triggerBadSound();
        void triggerMoneySound();
        void triggerSpendSound();
        void triggerMeepSound();
        void setRedLED(const uint8_t val);
        void setUpperGreenLED(const uint8_t val);
        void setLowerGreenLED(const uint8_t val);
        void setBlueLED(const uint8_t val);

};

#endif