#ifndef DETECTOR_H
#define DETECTOR_H

#include <stdint.h>

/**
 * Models a detection gate around an analog distance sensor.
 */
class Detector {
 private:
  /**
   * The pin number that the sensor is connected to.
   */
  const uint8_t SENSOR_PIN;

  /**
   * The threshold that the sensor reading has to cross to trigger the detection
   * gate.
   */
  const uint16_t DETECTION_THRESHOLD;

  /**
   * The update interval expressed in milliseconds.
   */
  const uint16_t UPDATE_INTERVAL_MILLIS;

  /**
   * The required timeout before a new trigger can happen, expressed in
   * milliseconds.
   */
  const uint16_t RECOVERY_TIMEOUT_MILLIS;

  /**
   * The timestamp in milliseconds of when this instance's sensor can be read
   * again.
   */
  uint32_t nextUpdate;

  /**
   * The timestamp in milliseconds of when this instance can trigger again.
   */
  uint32_t recoveryTime;

 public:
  /**
   * Creates a new instance of the Detector class.
   *
   * @param sensorPin The number of the analog pin to which the distance sensor
   * is connected
   * @param detectionThreshold The threshold that should be crossed to trigger
   * the detection gate
   * @param updateIntervalMillis The update interval expressed in milliseconds
   * @param recoveryTimeoutMillis The cooldown period expressed in milliseconds
   */
  Detector(uint8_t sensorPin,
           uint16_t detectionThreshold,
           uint16_t updateIntervalMillis,
           uint16_t recoveryTimeoutMillis);

  /**
   * Prepares this instance for usage.
   */
  void begin(void);

  /**
   * Reads the sensor.
   *
   * @param now The current time in milliseconds
   * @return True if the detection gate has been triggered
   */
  bool update(uint32_t now);
};

#endif
