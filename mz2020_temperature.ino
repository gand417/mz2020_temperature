#include <Adafruit_NeoPixel.h>
#include <Arduino_HTS221.h>

// Make Zurich 2020 badge LED configuration
#define LED_PIN 4
#define LED_COUNT 11

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// This routine runs once upon power on
void setup() {
  // Initialize serial monitor for debugging
  Serial.begin(9600);
  
  // Print an empty line
  Serial.println();
  Serial.println("Make Zurich 2020 Badge Thermometer");
  Serial.println("----------------------------------");

  // Initialize HTS221 sensor
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity / temperature sensor!");
    while (1);
  }
  
  // Inizialize Neopixel LED strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(42);
}

// This runs repeatedly, forever!
void loop() {
  // Read HTS221 sensor values
  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();

  // Print sensor values to Serial Monitor
  Serial.print("Temperature  = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity     = ");
  Serial.print(humidity);
  Serial.println(" %");


  // While the chip supports a range of -40°C to 120°C, 
  // we'll assume recommended badge operating conditions

  // Map temperature readings to rainbow colour scale
  int colour = map(temperature,-23,42,0,255);

  Serial.print("Wheel colour = ");
  Serial.println(colour);

  // Print an empty line
  Serial.println();

  // Set all pixels to the proper colour
  for(int i=0; i<LED_COUNT; i++) { 
    strip.setPixelColor(i, Wheel(colour));
  }
  
  // Send the updated pixel config to the LED strip
  strip.show();

  // Chillax for 100ms before next run
  delay(100);
}

// Colour wheel helper function:
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
