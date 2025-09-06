#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define DATA_PIN 12         // Change to your data pin

#define MATRIX_WIDTH 27      // prism matrix: 27, test matrix: 8
#define MATRIX_HEIGHT 7     // prism matrix: 7, test matrix: 8
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT) // Total number of LEDs

Adafruit_NeoPixel matrix(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ400); // Use NEO_KHZ400 for prism matrix AND NEO_KHZ800 for test matrix

void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.show();
}

void loop() {
  if (Serial.available() > 1) {
    uint8_t buffer[NUM_LEDS * 3];
    Serial.readBytes(buffer, NUM_LEDS * 3);
    for (int i = 0; i < NUM_LEDS; i++) {
      int idx = i * 3;
      matrix.setPixelColor(i, matrix.Color(buffer[idx], buffer[idx+1], buffer[idx+2]));
    }
    matrix.show();
    sleep(1000);
/*
  } else {
    static unsigned long lastBlink = 0;
    static bool ledOn = false;
    if (millis() - lastBlink > 1000) {
      lastBlink = millis();
      ledOn = !ledOn;
      uint32_t color = ledOn ? matrix.Color(5, 0, 0) : 0;
      for (int i = 0; i < NUM_LEDS; i++) {
        matrix.setPixelColor(i, color);
      }
      matrix.show();
      sleep(200);
    }*/
  }
}