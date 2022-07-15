Adafruit_NeoPixel stripA(strip_A.pixels, X_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripZ(strip_Z.pixels, Y_STRIP_PIN, NEO_GRB + NEO_KHZ800);

uint8_t Sintensity = 150;

void stripsInit(){
  stripA.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripZ.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripA.clear();
  stripZ.clear();

  stripA.setBrightness(Sintensity);
  stripZ.setBrightness(Sintensity);
}

void stripATest() {
  stripA.clear();
  
  for(int i=0; i<strip_A.pixels; i++) {
    stripA.setPixelColor(i, stripA.Color(0, 150, 0));
    stripA.show();
    delay(500);
  }
}

void CVtoStrip() {
  stripA.clear();
  stripZ.clear();
  uint8_t red   = toValue(R);
  uint8_t green = toValue(G);
  uint8_t blue  = toValue(B);
  uint32_t color = stripA.Color(red,green,blue);
  stripA.fill(color,0,stripA.numPixels());
  stripZ.fill(color,0,stripZ.numPixels());

  if(stripA.canShow()){
    stripA.show();
  }
  if(stripZ.canShow()){
    stripZ.show();
  }
}
