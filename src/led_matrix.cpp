#include <FastLED.h>

#define ESP32_LED_BUILTIN 2

#define LED_PIN 12
#define NUM_LEDS 200
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
  if (Serial.available()) {
    digitalWrite(ESP32_LED_BUILTIN, HIGH); // Turn LED on when receiving data
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].r = Serial.read();
      leds[i].g = Serial.read();
      leds[i].b = Serial.read();
    }
    FastLED.show();
  } else {
      digitalWrite(ESP32_LED_BUILTIN, LOW);
  }
  delay(10);
}