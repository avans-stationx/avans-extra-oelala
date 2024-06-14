#include "display.h"
#include <Arduino.h>
#include <GifDecoder.h>
#include "gif.h"
#include "globalsd.h"

typedef rgb24 rgb_t;
typedef SMLayerBackground<rgb_t, SM_BACKGROUND_OPTIONS_NONE>
    matrix_background_t;

const uint8_t MATRIX_WIDTH = 64;
const uint8_t MATRIX_HEIGHT = 96;
const uint8_t REFRESH_DEPTH = 48;
const uint8_t DMA_BUFFER_ROWS = 4;
const uint32_t PANEL_TYPE = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;
const uint8_t MATRIX_OPTIONS = SM_HUB75_OPTIONS_NONE;

SMARTMATRIX_ALLOCATE_BUFFERS(matrix,
                             MATRIX_WIDTH,
                             MATRIX_HEIGHT,
                             REFRESH_DEPTH,
                             DMA_BUFFER_ROWS,
                             PANEL_TYPE,
                             MATRIX_OPTIONS);

BACKGROUND_MEMSECTION rgb_t backgroundBitmap[2 * MATRIX_WIDTH * MATRIX_HEIGHT];
color_chan_t backgroundColorCorrectionLUT[sizeof(rgb_t) <= 3 ? 256 : 4096];
matrix_background_t background(backgroundBitmap,
                               MATRIX_WIDTH,
                               MATRIX_HEIGHT,
                               backgroundColorCorrectionLUT);

FsFile gif;
GifDecoder<MATRIX_WIDTH, MATRIX_HEIGHT, 12> gifDecoder;
const char* DEFAULT_GIF = "/gifs/default.gif";
const char* REACTION_GIF = "/gifs/reaction.gif";
const char* NO_PAPER_GIF = "/gifs/no-paper.gif";
const uint8_t REACTION_CYCLES = 2;
bool showingReaction;

const uint16_t FRAME_INTERVAL_MILLIS = 20;
uint32_t nextFrame;

void startDisplay() {
  matrix.addLayer(&background);
  matrix.begin();
  // matrix.setBrightness(127);

  gif.open(DEFAULT_GIF, O_RDONLY);
  showingReaction = false;

  gifDecoder.setScreenClearCallback(screenClearCallback);
  gifDecoder.setUpdateScreenCallback(updateScreenCallback);
  gifDecoder.setDrawPixelCallback(drawPixelCallback);
  gifDecoder.setFileSeekCallback(fileSeekCallback);
  gifDecoder.setFilePositionCallback(filePositionCallback);
  gifDecoder.setFileReadCallback(fileReadCallback);
  gifDecoder.setFileReadBlockCallback(fileReadBlockCallback);
  gifDecoder.setFileSizeCallback(fileSizeCallback);

  gifDecoder.startDecoding();

  background.fillScreen({0, 0, 0});
  background.swapBuffers();

  nextFrame = millis();
}

void updateDisplay(uint32_t now) {
  if (now < nextFrame) {
    return;
  }

  gifDecoder.decodeFrame();

  if (showingReaction && gifDecoder.getCycleNumber() >= REACTION_CYCLES) {
    gif.open(DEFAULT_GIF, O_RDONLY);
    gifDecoder.startDecoding();
    showingReaction = false;
  }

  nextFrame = now + FRAME_INTERVAL_MILLIS;
}

void showReactionDisplay() {
  gif.open(REACTION_GIF, O_RDONLY);
  gifDecoder.startDecoding();
  showingReaction = true;
}

void showNoPaperDisplay() {
  gif.open(NO_PAPER_GIF, O_RDONLY);
  gifDecoder.startDecoding();
  showingReaction = true;
}

void screenClearCallback(void) {
  background.fillScreen({0, 0, 0});
}

void updateScreenCallback(void) {
  background.swapBuffers();
}

void drawPixelCallback(int16_t x,
                       int16_t y,
                       uint8_t red,
                       uint8_t green,
                       uint8_t blue) {
  background.drawPixel(x, y, {red, green, blue});
}

bool fileSeekCallback(uint32_t position) {
  return gif.seek(position);
}

uint32_t filePositionCallback(void) {
  return gif.position();
}

int fileReadCallback(void) {
  return gif.read();
}

int fileReadBlockCallback(void* buffer, int numberOfBytes) {
  return gif.read((uint8_t*)buffer, numberOfBytes);
}

int fileSizeCallback(void) {
  return gif.size();
}
