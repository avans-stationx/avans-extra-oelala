#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(size_t capacity) : CAPACITY(capacity) {
  buffer = new uint8_t[capacity];
  head = 0;
  tail = 0;
}

CircularBuffer::~CircularBuffer() {
  delete[] buffer;
}

void CircularBuffer::push(uint8_t data) {
  increaseCount();

  if (tail == 0) {
    tail = CAPACITY - 1;
  } else {
    tail -= 1;
  }

  buffer[tail] = data;
}

uint8_t CircularBuffer::pop() {
  decreaseCount();

  uint8_t value = buffer[tail];

  tail += 1;

  if (tail >= CAPACITY) {
    tail = 0;
  }

  return value;
}

size_t CircularBuffer::popMany(uint8_t* buffer, size_t length) {
  size_t readable = count > length ? length : count;

  for (size_t i = 0; i < readable; i++) {
    buffer[i] = this->buffer[tail];

    tail += 1;

    if (tail >= CAPACITY) {
      tail = 0;
    }
  }

  count -= readable;

  return readable;
}

void CircularBuffer::unshift(uint8_t data) {
  increaseCount();

  head += 1;

  if (head >= CAPACITY) {
    head = 0;
  }

  buffer[head] = data;
}

uint8_t CircularBuffer::shift() {
  decreaseCount();

  uint8_t value = buffer[head];

  if (head == 0) {
    head = CAPACITY - 1;
  } else {
    head -= 1;
  }

  return value;
}

bool CircularBuffer::readable() {
  return count > 0;
}

bool CircularBuffer::writable() {
  return count < CAPACITY;
}

void CircularBuffer::increaseCount() {
  if (count < CAPACITY) {
    count += 1;
  }
}

void CircularBuffer::decreaseCount() {
  if (count > 0) {
    count -= 1;
  }
}
