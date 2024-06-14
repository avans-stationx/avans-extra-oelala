#ifndef RAINBOWLED_H
#define RAINBOWLED_H

#include <Adafruit_NeoPixel.h>

/**
 * Runs a color loop on a chain of NeoPixels.
 */
class RainbowLed {
 protected:
  /**
   * The amount that the hue will be incremented with on every update.
   */
  const uint16_t HUE_INCREMENT;

  /**
   * The hue of the displayed color.
   */
  uint16_t hue;

  /**
   * The saturation of the displayed color.
   */
  uint8_t saturation;

  /**
   * The brightness of the displayed color.
   */
  uint8_t brightness;

  /**
   * The hardware implementation of the leds.
   */
  Adafruit_NeoPixel leds;

  /**
   * The update interval expressed in milliseconds.
   */
  const uint16_t UPDATE_INTERVAL_MILLIS;

  const uint16_t COUNT;

  /**
   * The timestamp in milliseconds of when this instance can be animated
   * again.
   */
  uint32_t nextUpdate;

 public:
  /**
   * Creates a new instance of the RainbowLed class.
   *
   * @param count The amount of leds in the connected chain
   * @param pin The number of the pin to which the chain is connected
   * @param type The type of NeoPixels that are used
   * @param updateIntervalMillis The update interval expressed in milliseconds
   * @param hueIncrement The amount to increment the hue with on every update
   */
  RainbowLed(uint16_t count,
             uint8_t pin,
             neoPixelType type,
             uint16_t updateIntervalMillis,
             uint16_t hueIncrement);

  /**
   * Prepares this instance for usage.
   */
  void begin(void);

  /**
   * Sets the saturation of the displayed color.
   *
   * The new value will be used starting from the next update cycle.
   *
   * @param saturation The new saturation value
   */
  void setSaturation(uint8_t saturation);

  /**
   * Sets the brightness of the displayed color.
   *
   * The new value will be used starting from the next update cycle.
   *
   * @param brightness The new brightness value
   */
  void setBrightness(uint8_t brightness);

  /**
   * Animates the leds to the next hue.
   *
   * @param now The current time in milliseconds
   */
  virtual void update(uint32_t now);
};

#endif
