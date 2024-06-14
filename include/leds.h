#ifndef LEDS_H
#define LEDS_H

#include <FastLED.h>

void startLeds(void);
void updateLeds(uint32_t now);
void flashLeds(void);

#endif
