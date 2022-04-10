const uint8_t stripAPin = 2;
const uint8_t stripZPin = 3;

#include <Adafruit_NeoPixel.h>

uint8_t APixels = 16; // Popular NeoPixel ring size
uint8_t ZPixels = 16;

Adafruit_NeoPixel stripA(APixels, stripAPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripZ(ZPixels, stripZPin, NEO_GRB + NEO_KHZ800);

void stripsInit(){
  stripA.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripZ.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}

void stripATest() {
  stripA.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<APixels; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    stripA.setPixelColor(i, stripA.Color(0, 150, 0));

    stripA.show();   // Send the updated pixel colors to the hardware.

    delay(500); // Pause before next pass through loop
  }
}
