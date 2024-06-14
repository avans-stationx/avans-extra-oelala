#include "globalsd.h"

SdFat sd;

void startSD() {
  sd.begin(SdioConfig(DMA_SDIO));
}
