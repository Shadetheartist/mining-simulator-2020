#ifndef RESOURCES_H
#define RESOURCES_H

#include <Arduino.h>
#define NUM_LOCATIONS 4
#define NUM_RESOURCES 10

const char RESOURCE_0_NAME[] PROGMEM = {0x1e, ' ', 0};
const char RESOURCE_1_NAME[] PROGMEM = "Fe";
const char RESOURCE_2_NAME[] PROGMEM = "Cu";
const char RESOURCE_3_NAME[] PROGMEM = "Ag";
const char RESOURCE_4_NAME[] PROGMEM = "Au";
const char RESOURCE_5_NAME[] PROGMEM = "Pt";
const char RESOURCE_6_NAME[] PROGMEM = {0x7, 'E', 0};
const char RESOURCE_7_NAME[] PROGMEM = {0x7, 'R', 0};
const char RESOURCE_8_NAME[] PROGMEM = {0x7, 'D', 0};
const char RESOURCE_9_NAME[] PROGMEM = {0x7, 'G', 0};

const char *const RESOURCE_NAMES[] PROGMEM = {
    RESOURCE_0_NAME,
    RESOURCE_1_NAME,
    RESOURCE_2_NAME,
    RESOURCE_3_NAME,
    RESOURCE_4_NAME,
    RESOURCE_5_NAME,
    RESOURCE_6_NAME,
    RESOURCE_7_NAME,
    RESOURCE_8_NAME,
    RESOURCE_9_NAME,
};


//calculated for balance using gnu octave from files in the gnu_octave folder
const unsigned long RESOURCE_VALUES[NUM_RESOURCES] PROGMEM = { 1,16,125,796,4482,23182,112358,516989,2278331,9678399 };

const unsigned long LOCATION_RESOURCE_RARITIES[NUM_LOCATIONS][NUM_RESOURCES] PROGMEM = {
    {921959,71951,5615,438,34,3,0,0,0,0},
    {878909,106428,12887,1561,189,23,3,0,0,0},
    {813647,151626,28256,5266,981,183,34,6,1,0},
    {716043,203327,57737,16395,4655,1322,375,107,30,9},
};

#endif
