Adafruit_NeoPixel stripX(stripXdata.pixels, X_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripY(stripYdata.pixels, Y_STRIP_PIN, NEO_GRB + NEO_KHZ800);

void stripsInit(){
  stripX.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  stripY.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  //clean set pixels to 0
  stripX.updateLength(255);
  stripY.updateLength(255);
  stripX.clear();
  stripY.clear();
  stripX.show();
  stripY.show();
  stripX.updateLength(stripXdata.pixels);
  stripY.updateLength(stripYdata.pixels);
  
  stripX.setBrightness(stripXdata.intensity);
  stripY.setBrightness(stripYdata.intensity);
}

void stripXTest() {
  stripX.clear();
  
  for(int i=0; i<stripXdata.pixels; i++) {
    stripX.setPixelColor(i, stripX.Color(0, 150, 0));
    stripX.show();
    delay(500);
  }
}


void updateStripLength(int8_t function, uint8_t index){ //function == 1 iff ADD, -1 iff SUBTRACT
  if(function == ADD){
    if(SselectedStrip == STRIP_BOTH){
      if(stripXdata.pixels < 255){
        stripXdata.pixels++;
        stripYdata.pixels = stripXdata.pixels;
        stripX.updateLength(stripXdata.pixels);
        stripY.updateLength(stripYdata.pixels);
      }
    }
    else if(SselectedStrip == STRIP_X){
      if(stripXdata.pixels < 255){
        stripXdata.pixels++;
        stripX.updateLength(stripXdata.pixels);
      }
    }
    else if(SselectedStrip == STRIP_Y){
      if(stripYdata.pixels < 255){
        stripYdata.pixels++;
        stripY.updateLength(stripYdata.pixels);
      }
    }
  }
  else if(function == SUBTRACT){
    uint32_t noColor = stripX.Color(0,0,0);
    if(SselectedStrip == STRIP_BOTH){
      if(stripXdata.pixels > 1){
        stripX.setPixelColor(stripXdata.pixels-1,noColor);
        stripY.setPixelColor(stripXdata.pixels-1,noColor);
        stripXdata.pixels--;
        stripYdata.pixels = stripXdata.pixels;
        stripX.show();
        stripY.show();
        stripX.updateLength(stripXdata.pixels);
        stripY.updateLength(stripYdata.pixels);
      }
    }
    else if(SselectedStrip == STRIP_X){
      if(stripXdata.pixels > 1){
        stripX.setPixelColor(stripXdata.pixels-1,noColor);
        stripXdata.pixels--;
        stripX.show();
  
        stripX.updateLength(stripXdata.pixels);
      }
    }
    else if(SselectedStrip == STRIP_Y){
      if(stripYdata.pixels > 1){  
        stripY.setPixelColor(stripXdata.pixels-1,noColor);
        stripYdata.pixels--;
        stripY.show();
        stripY.updateLength(stripYdata.pixels);
      }
    }
  }
}

#define BRIGHTNESS_STEP 10

void updateStripIntensity(int8_t sign, uint8_t index){
  int16_t intensityX;
  int16_t intensityY;
  if(SselectedStrip == STRIP_BOTH || SselectedStrip == STRIP_X){
    intensityX = stripXdata.intensity + sign*BRIGHTNESS_STEP;

    if(intensityX > 255){
      intensityX = 255;
    }
    else if(intensityX < BRIGHTNESS_STEP){
      intensityX = BRIGHTNESS_STEP;
    }
    stripXdata.intensity = intensityX;
    stripX.setBrightness(stripXdata.intensity);
    Serial.print("Set stripX brightness to ");Serial.println(stripXdata.intensity);
  }
  
  if(SselectedStrip == STRIP_BOTH || SselectedStrip == STRIP_Y){
    intensityY = stripYdata.intensity + sign*BRIGHTNESS_STEP;

    if(intensityY > 255){
      intensityY = 255;
    }
    else if(intensityY < BRIGHTNESS_STEP){
      intensityY = BRIGHTNESS_STEP;
    }
    stripYdata.intensity = intensityY;
    stripY.setBrightness(stripYdata.intensity);
    Serial.print("Set stripY brightness to ");Serial.println(stripYdata.intensity);
  }
}

uint32_t colorLastX = 0;
uint32_t colorLastY = 0;

void CVtoStrip() {
  uint8_t red   = toValue(R);
  uint8_t green = toValue(G);
  uint8_t blue  = toValue(B);
  uint32_t color = stripX.Color(red,green,blue);
  if(!pauseAnimation){
      
    switch(stripXdata.animations[stripXdata.animationIndex]){
      case RGB_ANIMATION:
        stripX.fill(color,0,stripXdata.pixels);
        break;
      default:
        Serial.print("Now running animation #");Serial.println(stripXdata.animations[stripXdata.animationIndex]);
        break;
    }
    switch(stripYdata.animations[stripYdata.animationIndex]){
      case RGB_ANIMATION:
        stripY.fill(color,0,stripYdata.pixels);
        break;
      default:
        Serial.print("Now running animation #");Serial.println(stripYdata.animations[stripYdata.animationIndex]);
        break;
    }
  }

  if(!lightsOn && (stripX.getBrightness() != 0)){
    stripX.setBrightness(0);
    colorLastX = color; //store last shown color
  }
  else if(lightsOn && (stripX.getBrightness() == 0)){
    stripX.setBrightness(stripXdata.intensity);
    stripX.fill(colorLastX,0,stripXdata.pixels);
  }
  
  if(!lightsOn && (stripY.getBrightness() != 0)){
    stripY.setBrightness(0);
    colorLastY = color; //store last shown color
  }
  else if(lightsOn && (stripY.getBrightness() == 0)){
    stripY.setBrightness(stripXdata.intensity);
    stripY.fill(colorLastY,0,stripYdata.pixels);
  }

  if(stripX.canShow()){
    stripX.show();
  }  
  if(stripY.canShow()){
    stripY.show();
  }
}
