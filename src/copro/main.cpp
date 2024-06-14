#include <Arduino.h>
#include <RainbowLedWithFlash.h>

RainbowLedWithFlash leds(16, 3, NEO_BGR | NEO_KHZ800, 50, 50);
void trigger(void);

void setup() {
  leds.begin();
  leds.setBrightness(63);
  leds.setFlashDuration(10500);

  attachInterrupt(0, trigger, RISING);
}

void loop() {
  leds.update(millis());
}

void trigger() {
  leds.flashRainbow(true);
}
