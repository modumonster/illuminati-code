Adafruit_NeoPixel stripA(strip_A.pixels, X_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripZ(strip_Z.pixels, Y_STRIP_PIN, NEO_GRB + NEO_KHZ800);

void stripsInit(){
  stripA.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripZ.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripA.clear();
  stripZ.clear();
}

void stripATest() {
  stripA.clear();
  
  for(int i=0; i<strip_A.pixels; i++) {
    stripA.setPixelColor(i, stripA.Color(0, 150, 0));
    stripA.show();
    delay(500);
  }
}

uint8_t Sintensity = 255;

void CVtoStrip() {
  stripA.clear();
  uint8_t red   = map(toValue(R),0,255,0,Sintensity);
  uint8_t green = map(toValue(G),0,255,0,Sintensity);
  uint8_t blue  = map(toValue(B),0,255,0,Sintensity);
  //Serial.print(red);Serial.print(" - ");Serial.print(green);Serial.print(" - ");Serial.println(blue);
  for(uint8_t i = 0; i<strip_A.pixels; i++){
    stripA.setPixelColor(i, stripA.Color(red,green,blue));
  }
  stripA.show();
}
