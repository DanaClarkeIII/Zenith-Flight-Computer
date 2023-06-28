#include <FastLED.h>

#define NUM_LEDS 4 // Number of LEDs in your strip
#define DATA_PIN 14 // The pin your data line is connected to
#define COLOR_ORDER GRB // Order of colors in the bitstream. Change to RGB, GRB, GBR, etc. depending on your specific strip
#define LED_TYPE WS2812B // Type of LED strip. Change to WS2811, WS2812, WS2812B, etc. depending on your specific strip

CRGB leds[NUM_LEDS]; // This array will hold the color data for each LED

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // Initialize the LED strip
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) { // Loop over each LED
    leds[i] = CRGB::Red; // Set the color of the LED. Change to CRGB::Green, CRGB::Blue, etc. for different colors
    FastLED.show(); // Send the color data to the LED strip
    delay(30); // Wait a little bit before moving on to the next LED
  }
}