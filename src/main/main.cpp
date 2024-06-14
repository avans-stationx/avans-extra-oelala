#include <Arduino.h>
#include <Detector.h>
#include <TriggerFinger.h>
#include "display.h"
#include "gif.h"
#include "globalsd.h"

#include <Adafruit_NeoPixel.h>

#ifdef WITH_THERMAL
#include "thermal.h"
#endif

Detector sensor(A9, 300, 50, 1000);
TriggerFinger coprocessorTrigger(22, 50);
uint16_t TRIGGER_TIMEOUT_MILLIS = 30000;
uint32_t noTriggerUntil;
void handleTrigger(uint32_t now);

void setup() {
  sensor.begin();
  startSD();
  startDisplay();
  coprocessorTrigger.begin();

  noTriggerUntil = millis();

#ifdef WITH_THERMAL
  startPrinter();
#endif
}

void loop() {
  const uint32_t now = millis();

  coprocessorTrigger.update(now);

#ifdef WITH_THERMAL
  updatePrinter();
#endif

  updateDisplay(now);

  if (sensor.update(now)) {
    handleTrigger(now);
  }
}

void handleTrigger(uint32_t now) {
  if (now < noTriggerUntil) {
    return;
  }

  coprocessorTrigger.trigger();
  showReactionDisplay();

#ifdef WITH_THERMAL
  if (printerHasPaper()) {
    printReceipt();
  } else {
    showNoPaperDisplay();
  }
#endif

  noTriggerUntil = now + TRIGGER_TIMEOUT_MILLIS;
}
