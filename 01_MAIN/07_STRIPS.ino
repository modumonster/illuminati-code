Adafruit_NeoPixel stripA(strip_A.pixels, stripAPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripZ(strip_Z.pixels, stripZPin, NEO_GRB + NEO_KHZ800);

void stripsInit(){
  stripA.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripZ.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripA.clear();
  stripZ.clear();
}

void stripATest() {
  stripA.clear(); // Set all pixel colors to 'off'
  
  for(int i=0; i<strip_A.pixels; i++) { // For each pixel...

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
  uint8_t red = map(CV[R].Value,0,255,0,Sintensity);
  uint8_t green = map(CV[G].Value,0,255,0,Sintensity);
  uint8_t blue = map(CV[B].Value,0,255,0,Sintensity);
  //Serial.print(red);Serial.print(" - ");Serial.print(green);Serial.print(" - ");Serial.println(blue);
  for(uint8_t i = 0; i<strip_A.pixels; i++){
  stripA.setPixelColor(i, stripA.Color(red,green,blue));
  }
  stripA.show();   // Send the updated pixel colors to the hardware.
}
