#ifndef THERMAL_H
#define THERMAL_H

#include <Adafruit_Thermal.h>

void startPrinter(void);
void updatePrinter(void);
void printReceipt(void);
bool printerHasPaper(void);

#endif
