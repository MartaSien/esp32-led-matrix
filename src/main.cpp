#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define DATA_PIN 5         // Change to your data pin
#define NUM_LEDS 64        // 8x8 matrix

Adafruit_NeoPixel matrix(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (Serial.available() >= 192) { // 8x8x3 bytes
    uint8_t buffer[192];
    Serial.readBytes(buffer, 192);
    for (int i = 0; i < NUM_LEDS; i++) {
      int idx = i * 3;
      matrix.setPixelColor(i, matrix.Color(buffer[idx], buffer[idx+1], buffer[idx+2]));
    }
    matrix.show();
  }
}