/*
Licensed under MIT license. See full license in LICENSE file.

Author: Jarett Rude
*/

// must include NeoPixel library
#include <Adafruit_NeoPixel.h>

// constants won't change. They're used here to set pin numbers:
const int buttonPin   = 3;
const int ringPin     = 8;
const int ringPixels  = 24;
const int flashPin    = 7;
const int flashPixels = 140;

// define LED ring
Adafruit_NeoPixel ring(ringPixels, ringPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel flash(flashPixels, flashPin, NEO_GRB + NEO_KHZ800);

// variables will change:
boolean oldState = LOW;// variable for reading the pushbutton status

void setup() {

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  ring.begin(); // Initialize NeoPixel strip object (REQUIRED)
  ring.show();  // Initialize all pixels to 'off'
  flash.begin(); // Initialize NeoPixel strip object (REQUIRED)
  flash.show();  // Initialize all pixels to 'off'
  flash.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  // read the state of the pushbutton value:
  boolean newState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  // Check if state changed from high to low (button press).

  if ((newState == HIGH) && (oldState == LOW)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still high after debounce.
    newState = digitalRead(buttonPin);
    if (newState == HIGH) {     // Yes, still high
      // turn LED on:
      flashColorWipe(flash.Color(255, 255, 255), 1);    // White
      ringColorWipe(ring.Color(255,   0,   0), 40);    // Red
      ringColorWipe(ring.Color(255,  69,   0), 40);    // Orange
      ringColorWipe(ring.Color(255, 223,   0), 40);    // Yellow
      ringColorWipe(ring.Color(  0, 255,   0), 30);    // Green
      ringColorWipe(ring.Color(255, 255, 255), 15
      );    // White
      delay(5000);
    }
    ringColorWipe(ring.Color(  0,   0,   0), 50);    // Black/off
    flashColorWipe(flash.Color(  0,   0,   0), 5);    // Black/off
  }
  oldState = newState;
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void ringColorWipe(uint32_t color, int wait) {
  for (int i = 0; i < ring.numPixels(); i++) { // For each pixel in strip...
    ring.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    ring.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void flashColorWipe(uint32_t color, int wait) {
  for (int i = 0; i < flash.numPixels(); i++) { // For each pixel in strip...
    flash.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    flash.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
