#ifndef DISPLAY_H
#define DISPLAY_H

#include <MatrixHardware_Teensy4_ShieldV5.h>
#include <SmartMatrix.h>

void startDisplay(void);
void updateDisplay(uint32_t now);
void showReactionDisplay(void);
void showNoPaperDisplay(void);

#endif
