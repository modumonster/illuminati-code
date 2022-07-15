Adafruit_NeoPixel stripX(stripXdata.pixels, X_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripY(stripYdata.pixels, Y_STRIP_PIN, NEO_GRB + NEO_KHZ800);

uint8_t Sintensity = 150;

void stripsInit(){
  stripX.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripY.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripX.clear();
  stripY.clear();

  stripX.setBrightness(Sintensity);
  stripY.setBrightness(Sintensity);
}

void stripXTest() {
  stripX.clear();
  
  for(int i=0; i<stripXdata.pixels; i++) {
    stripX.setPixelColor(i, stripX.Color(0, 150, 0));
    stripX.show();
    delay(500);
  }
}

void CVtoStrip() {
  stripX.clear();
  stripY.clear();
  uint8_t red   = toValue(R);
  uint8_t green = toValue(G);
  uint8_t blue  = toValue(B);
  uint32_t color = stripX.Color(red,green,blue);
  stripX.fill(color,0,stripXdata.pixels);
  stripY.fill(color,0,stripYdata.pixels);

  if(stripX.canShow()){
    stripX.show();
  }
  if(stripY.canShow()){
    stripY.show();
  }
}
