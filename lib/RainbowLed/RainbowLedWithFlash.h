#ifndef RAINBOWLEDWITHFLASH_H
#define RAINBOWLEDWITHFLASH_H

#include <Adafruit_NeoPixel.h>
#include "RainbowLed.h"

/**
 * Runs a color loop on a chain of NeoPixels that can be paused to function as a
 * camera flash.
 */
class RainbowLedWithFlash : public RainbowLed {
 private:
  /**
   * The default flash duration, expressed in milliseconds.
   */
  uint32_t flashDuration;

  const uint16_t HUE_STEP;
  uint16_t nextAnimationHueOffset;
  uint32_t animationEndMillis;

  /**
   * Gives direct access to the flash, if true, the light will be in the flash
   * state.
   */
  bool flashOverride;

  /**
   * Changes the color of the leds to pure white.
   */
  void showWhite(void);

  void showRainbow(uint16_t offset);

 public:
  /**
   * Creates a new instance of the RainbowLedWithFlash class.
   *
   * @param count The amount of leds in the connected chain
   * @param pin The number of the pin to which the chain is connected
   * @param type The type of NeoPixels that are used
   * @param updateIntervalMillis The update interval expressed in milliseconds
   * @param hueIncrement The amount to increment the hue with on every update
   */
  RainbowLedWithFlash(uint8_t count,
                      uint8_t pin,
                      neoPixelType type,
                      uint16_t updateIntervalMillis,
                      uint16_t hueIncrement);

  /**
   * Animates the leds to the next hue.
   *
   * @param now The current time in milliseconds
   */
  void update(uint32_t now) override;

  /**
   * Turns on the flash for the default duration.
   */
  void flash(void);

  /**
   * Turns on the flash for the given duration.
   *
   * @param duration The duration of the flash, expressed in milliseconds
   */
  void flash(uint32_t duration);

  void flashRainbow(bool animate);
  void flashRainbow(uint32_t duration, bool animate);

  /**
   * Sets the default flash duration.
   *
   * @param duration The new default duration, expressed in milliseconds
   */
  void setFlashDuration(uint32_t duration);

  /**
   * Overrides the automatic flash state.
   *
   * @param state If true, the light will be in the flash state
   */
  void setFlashOverride(bool state);
};

#endif
