#ifndef THERMALPRINTER_H
#define THERMALPRINTER_H

#include <Print.h>
#include <Stream.h>

struct ThermalPrinterTextStyle {
  bool bold;
  bool doubleHeight;
  bool doubleWidth;
  bool inverse;
  bool underline;
  bool strike;
};

class ThermalPrinter : public Print {
 private:
  const Stream* STREAM;
  uint8_t printMode;
  void writePrintMode(void);
  void setPrintMode(uint8_t mask);
  void unsetPrintMode(uint8_t mask);

 public:
  ThermalPrinter(Stream* stream);
  size_t write(uint8_t data);
  void begin(void);
  void update(void);

  void normal(void);
  void setBold(bool state);
  void setDoubleHeight(bool state);
  void setDoubleWidth(bool state);
  void setInverse(bool state);
  void setUnderline(bool state);
};

#endif
