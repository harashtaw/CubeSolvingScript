#include <LedControl.h>

String InBytes;
const int DIN_PIN = 12;
const int CS_PIN = 10;
const int CLK_PIN = 11;
String alg;
long algint;
const uint64_t IMAGES[] = {
  0x202020a870200000,
  0x2070a82020200000,
  0x040e150404040000,
  0x040404150e040000,
  0x00000008047e0408,
  0x00000010207e2010,
  0x10207e2010000000,
  0x08047e0408000000,
  0x38040202e2c4b800,
  0x384080808e463a00,
  0x3a468e8080403800,
  0xb8c4e20202043800
};
const int IMAGES_LEN = sizeof(IMAGES) / 8;


LedControl display = LedControl(DIN_PIN, CLK_PIN, CS_PIN);


void setup() {
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 10);
  Serial.begin(9600);
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}

int i = 0;

void loop() {
  if (Serial.available()) {
    alg = Serial.readStringUntil('\n');
    algint = alg.toInt();
    Serial.print(algint);
    displayImage(IMAGES[algint]);
    delay(1000);
    displayImage(IMAGES[13]);
    delay(500);
  }
}
