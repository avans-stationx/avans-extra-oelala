#ifndef TRIGGERFINGER_H
#define TRIGGERFINGER_H

#include <inttypes.h>

class TriggerFinger {
 private:
  const uint8_t PIN;
  const uint16_t RELEASE_MILLIS;
  const bool INVERTED;
  uint32_t releaseAt;
  bool triggered;

 public:
  TriggerFinger(uint8_t pin, uint16_t releaseMillis, bool inverted = false);
  void begin(void);
  void trigger(void);
  void update(void);
  void update(uint32_t now);
};

#endif
