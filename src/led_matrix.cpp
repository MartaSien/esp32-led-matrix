#include <FastLED.h>

#define ESP32_LED_BUILTIN 2

#define LED_PIN 12

#define MATRIX_WIDTH 27
#define MATRIX_HEIGHT 7
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT)
#define BRIGHTNESS 50
#define LED_TYPE WS2811
#define COLOR_ORDER RGB

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(ESP32_LED_BUILTIN, OUTPUT); // Initialize built-in LED pin
}

void loop() {
  if (Serial.available() > NUM_LEDS) { // It should be NUM_LEDS * 3 bytes but some margin was needed
    digitalWrite(ESP32_LED_BUILTIN, HIGH);
    uint8_t buffer[NUM_LEDS * 3];
    Serial.readBytes(buffer, NUM_LEDS * 3); // Read all bytes at once
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].r = buffer[i * 3];
      leds[i].g = buffer[i * 3 + 1];
      leds[i].b = buffer[i * 3 + 2];
    }
    FastLED.show();
  } else {
    digitalWrite(ESP32_LED_BUILTIN, LOW);
  }
  delay(10);
}