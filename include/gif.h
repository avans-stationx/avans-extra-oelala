#ifndef GIF_H
#define GIF_H

#include <inttypes.h>

void screenClearCallback(void);
void updateScreenCallback(void);
void drawPixelCallback(int16_t x,
                       int16_t y,
                       uint8_t red,
                       uint8_t green,
                       uint8_t blue);
bool fileSeekCallback(uint32_t position);
uint32_t filePositionCallback(void);
int fileReadCallback(void);
int fileReadBlockCallback(void* buffer, int numberOfBytes);
int fileSizeCallback(void);

#endif
