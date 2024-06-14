#include "thermal.h"
#include <Arduino.h>
#include <qrcode.h>
#include "globalsd.h"
#include "oelala.h"

Adafruit_Thermal printer(&Serial1, 8192);

void loadLines(void);
void wrapLine(char* destination, char* source);
void loadLogo(void);
void titleStyle(void);
void bigTextStyle(void);
void printQrCode(QRCode qrCode);

uint16_t lineCount;
char** lines;
const uint16_t MAX_LINE_LENGTH = 512;
const uint8_t MAX_LINE_COLUMNS = 30;

QRCode qrCode;
uint8_t* qrCodeData;

const char* LOGO_FILENAME = "/logo.bmp";
const uint16_t LOGO_WIDTH = 384;
const uint16_t LOGO_HEIGHT = 75;
const size_t LOGO_BYTE_SIZE = ((LOGO_WIDTH * LOGO_HEIGHT) + 7) / 8;
uint8_t logo[LOGO_BYTE_SIZE];

void startPrinter() {
  Serial1.begin(9600);
  printer.begin();

  delay(1000);

  loadLines();

  const uint8_t qrVersion = 2;
  size_t qrCodeDataSize = qrcode_getBufferSize(qrVersion);
  qrCodeData = new uint8_t[qrCodeDataSize];
  qrcode_initText(&qrCode, qrCodeData, qrVersion, ECC_LOW,
                  "https://bit.ly/3QMXXzu?r=qr");

  loadLogo();

  printer.wake();
  bigTextStyle();
  printer.println("Avans Extra Sorry Installation by StationX");
  printer.feed(2);

  printer.setDefault();

  printer.printf("Loaded logo, using %ub\n", LOGO_BYTE_SIZE);
  printer.printf("Pregenerated QR code, using %ub\n", qrCodeDataSize);

  printer.printf("Loaded %u %s\n", lineCount,
                 lineCount != 1 ? "lines" : "line");
  for (size_t i = 0; i < lineCount; i++) {
    printer.printf("%u: %s\n", i + 1, lines[i]);
  }

  printer.feed(1);
  printer.println("Ready to oelala!");
  printer.feed(2);

  printer.sleep();
}

void updatePrinter() {
  printer.update();
}

void loadLines() {
  FsFile linesFile;
  linesFile.open("/lines.txt", O_RDONLY);

  lineCount = 0;

  while (linesFile.available()) {
    char line[MAX_LINE_LENGTH];
    size_t length = linesFile.readBytesUntil('\n', line, MAX_LINE_LENGTH);

    if (length > 0) {
      lineCount += 1;
    }
  }

  linesFile.seek(0);

  lines = new char*[lineCount];

  for (size_t i = 0; i < lineCount; i++) {
    char line[MAX_LINE_LENGTH];
    memset(line, 0, MAX_LINE_LENGTH);
    size_t length = linesFile.readBytesUntil('\n', line, MAX_LINE_LENGTH);

    line[length - 1] = '\0';

    char* wrappedLine = new char[length];
    memset(wrappedLine, 0, length);
    wrapLine(wrappedLine, line);

    lines[i] = wrappedLine;
  }

  linesFile.close();
}

void wrapLine(char* destination, char* source) {
  uint8_t substringLength = 0;

  char* word = strtok(source, " ");

  while (word != nullptr) {
    size_t length = strlen(word);

    if (substringLength + length + 1 > MAX_LINE_COLUMNS) {
      strcat(destination, "\n");
      substringLength = length;
    } else if (substringLength > 0) {
      strcat(destination, " ");
      substringLength += length + 1;
    } else {
      substringLength += length;
    }

    strcat(destination, word);

    word = strtok(nullptr, " ");
  }
}

void loadLogo() {
  FsFile logoFile;
  logoFile.open(LOGO_FILENAME);
  const uint8_t bmpHeaderSize = 64;
  logoFile.seekSet(bmpHeaderSize);
  memset(logo, 0xff, LOGO_BYTE_SIZE);
  logoFile.readBytes(logo, LOGO_BYTE_SIZE);
  logoFile.close();
}

void titleStyle() {
  printer.setDefault();
  printer.boldOn();
  printer.underlineOn(1);
  printer.setSize('L');
  printer.justify('C');
}

void bigTextStyle() {
  printer.setDefault();
  printer.setFont('A');
  printer.boldOn();
  printer.setSize('M');
  printer.justify('C');
}

void printReceipt() {
  printer.wake();

  // titleStyle();
  // printer.println("OELALA");
  printer.printBitmap(OELALA_LOGO_WIDTH, OELALA_LOGO_HEIGHT, OELALA_LOGO, false);
  printer.feed(2);

  bigTextStyle();
  size_t lineIndex = random(0, lineCount);
  printer.println(lines[lineIndex]);
  printer.feed(2);

  printQrCode(qrCode);
  printer.feed(1);

  printer.setDefault();
  printer.justify('C');
  printer.println("Uitgevoerd door StationX");
  printer.feed(4);

  printer.sleep();
}

bool printerHasPaper() {
  return printer.hasPaper();
}

void printQrCode(QRCode qrCode) {
  printer.setDefault();
  printer.justify('C');
  printer.setLineHeight(0);

  for (size_t y = 0; y < qrCode.size; y += 2) {
    for (size_t x = 0; x < qrCode.size; x++) {
      if (qrcode_getModule(&qrCode, x, y) &&
          qrcode_getModule(&qrCode, x, (y + 1))) {
        // Black square above black square
        printer.write(219);
      } else if (!qrcode_getModule(&qrCode, x, y) &&
                 qrcode_getModule(&qrCode, x, (y + 1))) {
        // White square above black square
        printer.write(220);
      } else if (qrcode_getModule(&qrCode, x, y) &&
                 !qrcode_getModule(&qrCode, x, (y + 1))) {
        // Black square above white square
        printer.write(223);
      } else {
        // White square above white square
        printer.print(" ");
      }
    }

    printer.print("\n");
  }

  printer.feed(2);
}
