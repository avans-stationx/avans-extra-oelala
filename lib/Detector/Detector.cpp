#include "Detector.h"
#include <Arduino.h>

Detector::Detector(uint8_t sensorPin,
                   uint16_t detectionThreshold,
                   uint16_t updateIntervalMillis,
                   uint16_t recoveryTimeoutMillis)
    : SENSOR_PIN(sensorPin),
      DETECTION_THRESHOLD(detectionThreshold),
      UPDATE_INTERVAL_MILLIS(updateIntervalMillis),
      RECOVERY_TIMEOUT_MILLIS(recoveryTimeoutMillis) {}

void Detector::begin() {
  nextUpdate = millis() + UPDATE_INTERVAL_MILLIS;
}

bool Detector::update(uint32_t now) {
  if (now < nextUpdate) {
    return false;
  }

  uint16_t sample = analogRead(SENSOR_PIN);
  bool triggered = sample > DETECTION_THRESHOLD;

  nextUpdate = now + UPDATE_INTERVAL_MILLIS;

  if (triggered && now >= recoveryTime) {
    recoveryTime = now + RECOVERY_TIMEOUT_MILLIS;
    return true;
  }

  if (triggered) {
    recoveryTime = now + RECOVERY_TIMEOUT_MILLIS;
  }

  return false;
}
