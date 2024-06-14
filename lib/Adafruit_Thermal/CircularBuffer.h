#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <inttypes.h>
#include <stddef.h>

class CircularBuffer {
 public:
  CircularBuffer(size_t capacity);
  ~CircularBuffer(void);
  void push(uint8_t data);
  uint8_t pop(void);
  size_t popMany(uint8_t* buffer, size_t length);
  void unshift(uint8_t data);
  uint8_t shift(void);
  bool readable(void);
  bool writable(void);

 private:
  const size_t CAPACITY;
  uint8_t* buffer;
  size_t count;
  size_t head;
  size_t tail;
  void increaseCount(void);
  void decreaseCount(void);
};

#endif
