#include <Adafruit_NeoPixel.h>
#include <Arduino_APDS9960.h>

// Make Zurich 2020 badge LED configuration
#define LED_PIN 4
#define LED_COUNT 11

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// This routine runs once upon power on
void setup() {
  // Initialize serial monitor for debugging
  Serial.begin(9600);

  // Initialize ADPS9660 sensor
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
  
  // Inizialize Neopixel LED strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255);
}

// Global variable to keep track of proximity reading
int proximity = 0;

// This runs repeatedly, forever
void loop() {
  if (APDS.proximityAvailable()) {
    proximity = APDS.readProximity();
  }
  int brightness = 255 - proximity;
  for(int i=0; i<LED_COUNT; i++) { // For each pixel...
    strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
  }
  strip.show();   // Send the updated pixel colors to the hardware.
}
