#include "RainbowLed.h"

RainbowLed::RainbowLed(uint16_t count,
                       uint8_t pin,
                       neoPixelType type,
                       uint16_t updateIntervalMillis,
                       uint16_t hueIncrement)
    : HUE_INCREMENT(hueIncrement),
      leds(count, pin, type),
      UPDATE_INTERVAL_MILLIS(updateIntervalMillis),
      COUNT(count) {
  hue = 0;
  saturation = 255;
  brightness = 255;
}

void RainbowLed::begin() {
  leds.begin();
  nextUpdate = millis();
}

void RainbowLed::setSaturation(uint8_t saturation) {
  this->saturation = saturation;
}

void RainbowLed::setBrightness(uint8_t brightness) {
  this->brightness = brightness;
}

void RainbowLed::update(uint32_t now) {
  if (now < nextUpdate) {
    return;
  }

  leds.fill(leds.ColorHSV(hue, saturation, brightness));
  leds.show();
  hue += HUE_INCREMENT;
  nextUpdate = now + UPDATE_INTERVAL_MILLIS;
}
