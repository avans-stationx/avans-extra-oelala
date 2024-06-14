#include "ThermalPrinter.h"

ThermalPrinter::ThermalPrinter(Stream* stream) : STREAM(stream) {}

void ThermalPrinter::writePrintMode() {}

void ThermalPrinter::setPrintMode(uint8_t mask) {
  printMode |= mask;
  writePrintMode();
}

void ThermalPrinter::unsetPrintMode(uint8_t mask) {
  printMode &= ~mask;
  writePrintMode();
}

void ThermalPrinter::normal(void) {
  printMode = 0;
  writePrintMode();
}

void ThermalPrinter::setBold(bool state) {
  uint8_t mask = 1 << 3;

  if (state) {
    setPrintMode(mask);
  } else {
    unsetPrintMode(mask);
  }
}

void ThermalPrinter::setDoubleHeight(bool state) {
  uint8_t mask = 1 << 4;

  if (state) {
    setPrintMode(mask);
  } else {
    unsetPrintMode(mask);
  }
}
