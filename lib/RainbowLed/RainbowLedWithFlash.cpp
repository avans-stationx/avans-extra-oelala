#include "RainbowLedWithFlash.h"

RainbowLedWithFlash::RainbowLedWithFlash(uint8_t count,
                                         uint8_t pin,
                                         neoPixelType type,
                                         uint16_t updateIntervalMillis,
                                         uint16_t hueIncrement)
    : RainbowLed(count, pin, type, updateIntervalMillis, hueIncrement),
      HUE_STEP(0xffff / count) {
  flashDuration = 200;
  flashOverride = false;
  animationEndMillis = millis();
}

void RainbowLedWithFlash::update(uint32_t now) {
  if (flashOverride) {
    return;
  }

  if (now < animationEndMillis) {
    nextAnimationHueOffset += HUE_INCREMENT;
    showRainbow(nextAnimationHueOffset);
  } else {
    RainbowLed::update(now);
  }
}

void RainbowLedWithFlash::flash() {
  flash(flashDuration);
}

void RainbowLedWithFlash::flash(uint32_t duration) {
  showWhite();
  nextUpdate = millis() + duration;
}

void RainbowLedWithFlash::flashRainbow(bool animate) {
  flashRainbow(flashDuration, animate);
}

void RainbowLedWithFlash::flashRainbow(uint32_t duration, bool animate) {
  showRainbow(0);

  if (animate) {
    animationEndMillis = millis() + duration;
  } else {
    nextUpdate = millis() + duration;
  }
}

void RainbowLedWithFlash::showWhite() {
  leds.fill(0xffffffff);
  leds.show();
}

void RainbowLedWithFlash::showRainbow(uint16_t offset) {
  for (uint16_t i = 0; i < COUNT; i++) {
    leds.setPixelColor(
        i, leds.ColorHSV(offset + (i * HUE_STEP), saturation, brightness));
  }

  leds.show();
}

void RainbowLedWithFlash::setFlashDuration(uint32_t duration) {
  flashDuration = duration;
}

void RainbowLedWithFlash::setFlashOverride(bool state) {
  flashOverride = state;

  if (flashOverride) {
    showWhite();
    return;
  }

  nextUpdate = millis();
}
