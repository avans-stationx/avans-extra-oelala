#include "TriggerFinger.h"
#include <Arduino.h>

TriggerFinger::TriggerFinger(uint8_t pin, uint16_t releaseMillis, bool inverted)
    : PIN(pin), RELEASE_MILLIS(releaseMillis), INVERTED(inverted) {
  releaseAt = millis();
  triggered = false;
}

void TriggerFinger::begin() {
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, INVERTED);
}

void TriggerFinger::trigger() {
  digitalWrite(PIN, !INVERTED);
  releaseAt = millis() + RELEASE_MILLIS;
  triggered = true;
}

void TriggerFinger::update() {
  update(millis());
}

void TriggerFinger::update(uint32_t now) {
  if (!triggered) {
    return;
  }

  if (now < releaseAt) {
    return;
  }

  digitalWrite(PIN, INVERTED);
  triggered = false;
}
