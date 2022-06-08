uint8_t APixels = 16; // Popular NeoPixel ring size
uint8_t ZPixels = 16;

Adafruit_NeoPixel stripA(APixels, stripAPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripZ(ZPixels, stripZPin, NEO_GRB + NEO_KHZ800);

void stripsInit(){
  stripA.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripZ.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripA.clear();
  stripZ.clear();
}

void stripATest() {
  stripA.clear(); // Set all pixel colors to 'off'
  
  for(int i=0; i<APixels; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    stripA.setPixelColor(i, stripA.Color(0, 150, 0));

    stripA.show();   // Send the updated pixel colors to the hardware.

    delay(500); // Pause before next pass through loop
  }
}
uint8_t Sintensity = 255;

void CVtoStrip() {
  stripA.clear();
  uint8_t red = map(CVValues[R],(Rmin+Rmax)/2,Rmax,0,Sintensity);
  uint8_t green = map(CVValues[G],(Gmin+Gmax)/2,Gmax,0,Sintensity);
  uint8_t blue = map(CVValues[B],(Bmin+Bmax)/2,Bmax,0,Sintensity);
  //Serial.print(red);Serial.print(" - ");Serial.print(green);Serial.print(" - ");Serial.println(blue);
  for(uint8_t i = 0; i<APixels; i++){
  stripA.setPixelColor(i, stripA.Color(red,green,blue));
  }
  stripA.show();   // Send the updated pixel colors to the hardware.
}
