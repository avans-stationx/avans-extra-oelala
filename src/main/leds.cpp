// #include "leds.h"

// const uint8_t LED_COUNT = 16;
// CRGB leds[LED_COUNT];
// uint8_t hue;

// uint32_t nextUpdate;
// const uint16_t UPDATE_INTERVAL_MILLIS = 50;
// const uint16_t FLASH_DURATION_MILLIS = 200;

// void startLeds() {
//   FastLED.addLeds<WS2812B, 22, GRB>(leds, LED_COUNT);
//   // .setCorrection(TypicalLEDStrip);
//   FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
//   hue = 0;
//   nextUpdate = millis();
// }

// void updateLeds(uint32_t now) {
//   if (now < nextUpdate) {
//     return;
//   }

//   CRGB color = CHSV(hue, 255, 63);

//   fill_solid(leds, LED_COUNT, color);
//   FastLED.show();

//   nextUpdate += UPDATE_INTERVAL_MILLIS;
// }

// void flashLeds() {
//   fill_solid(leds, LED_COUNT, CRGB::White);
//   FastLED.show();

//   nextUpdate += FLASH_DURATION_MILLIS;
// }
