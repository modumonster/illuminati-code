const uint16_t debounceMillis = 20;
const uint16_t longPressMillis = 500;
const uint16_t doubleClickMillis = 0; //disable double click

Button2 btnMode, btnPlus, btnMinus, btnSelect;

void buttonInit(){
  btnMode.begin(MODE_BTN_PIN);
  btnPlus.begin(PLUS_BTN_PIN);
  btnMinus.begin(MNUS_BTN_PIN);
  btnSelect.begin(SLCT_BTN_PIN);
  
  btnMode.setClickHandler(clickHandler);
  btnPlus.setClickHandler(clickHandler);
  btnMinus.setClickHandler(clickHandler);
  btnSelect.setClickHandler(clickHandler);

  btnMode.setLongClickHandler(lpHandler);
  btnPlus.setLongClickHandler(lpHandler);
  btnMinus.setLongClickHandler(lpHandler);
  btnSelect.setLongClickHandler(lpHandler);

  btnMode.setLongClickDetectedHandler(lpDetectedHandler);
  btnPlus.setLongClickDetectedHandler(lpDetectedHandler);
  btnMinus.setLongClickDetectedHandler(lpDetectedHandler);
  btnSelect.setLongClickDetectedHandler(lpDetectedHandler);

  btnMode.setDebounceTime(debounceMillis);
  btnPlus.setDebounceTime(debounceMillis);
  btnMinus.setDebounceTime(debounceMillis);
  btnSelect.setDebounceTime(debounceMillis);

  btnMode.setDoubleClickTime(doubleClickMillis);
  btnPlus.setDoubleClickTime(doubleClickMillis);
  btnMinus.setDoubleClickTime(doubleClickMillis);
  btnSelect.setDoubleClickTime(doubleClickMillis);

  btnMode.setLongClickTime(longPressMillis);
  btnPlus.setLongClickTime(longPressMillis);
  btnMinus.setLongClickTime(longPressMillis);
  btnSelect.setLongClickTime(longPressMillis);
}

#define MODE    4
#define PLUS    5
#define MINUS   6
#define SELECT  7

void buttons(){
  btnMode.loop();
  btnPlus.loop();
  btnMinus.loop();
  btnSelect.loop();
}

uint8_t modeAndPlus     = 0;
uint8_t minusAndSelect  = 0;
uint8_t plusAndMinus    = 0;
uint8_t modeAndSelect   = 0;

void clickHandler(Button2& btn){
  if (btn.getType() == single_click) {        
    uint8_t btnId = btn.getID();
      switch(menuPage){
        case GAIN:
            if(btnId == MODE){
              Serial.println("GAIN\t| Mode pressed");
              if(GselectedCV == A){
                lampALinear = !lampALinear;
              }
              else if(GselectedCV == Z){
                lampZLinear = !lampZLinear;
              }
            }
            else if(btnId == PLUS){     //autoMin/-5/-2.5/-0 minimum voltage
              CV[GselectedCV].minIndex++;
              if(CV[GselectedCV].minIndex > 3){
                CV[GselectedCV].minIndex = 0;
              }
              if(CV[GselectedCV].minIndex == 0){
                CV[GselectedCV].autoMin = true;
              }
              else{
                CV[GselectedCV].autoMin = false;
              }
              Serial.print("GAIN\t| Min of CV ");Serial.print(GselectedCV); Serial.print(" set to "); Serial.println(CV[GselectedCV].minIndex);
            }
            else if(btnId == MINUS){    //autoMax/5/2.5/0 maximum voltage
              CV[GselectedCV].maxIndex++;
              if(CV[GselectedCV].maxIndex > 3){
                CV[GselectedCV].maxIndex = 0;
              }
              if(CV[GselectedCV].maxIndex == 0){
                CV[GselectedCV].autoMax = true;
              }
              else{
                CV[GselectedCV].autoMax = false;
              }
              Serial.print("GAIN\t| Max of CV ");Serial.print(GselectedCV); Serial.print(" set to "); Serial.println(CV[GselectedCV].maxIndex);
            }
            else if(btnId == SELECT){
              GselectedCV++;
              if(GselectedCV > 5){
                GselectedCV = 0;
              }
              Serial.print("GAIN\t| Selected CV is now ");Serial.println(GselectedCV);
            }
          break;
        case DECAY:
            if(btnId == MODE){
              Serial.println("DECAY\t| Mode pressed");
            }
            else if(btnId == PLUS){
              CV[DselectedCV].riseTime++;
              if(CV[DselectedCV].riseTime > 2){
                CV[DselectedCV].riseTime = 0;
              }
              Serial.print("DECAY\t| Rise of CV ");Serial.print(DselectedCV); Serial.print(" set to "); Serial.println(CV[DselectedCV].riseTime);
            }
            else if(btnId == MINUS){
              CV[DselectedCV].fallTime++;
              if(CV[DselectedCV].fallTime > 2){
                CV[DselectedCV].fallTime = 0;
              }
              Serial.print("DECAY\t| Fall of CV ");Serial.print(DselectedCV); Serial.print(" set to "); Serial.println(CV[DselectedCV].fallTime);
            }
            else if(btnId == SELECT){
              DselectedCV++;
              if(DselectedCV > 5){
                DselectedCV = 0;
              }
            Serial.print("DECAY\t| Selected CV is now ");Serial.println(DselectedCV);
            }
          break;
        case STEPS:                                       //should be probably renamed to something like animation/program
            if(btnId == MODE){
              Serial.println("STEPS \t| Mode pressed");
            }
            else if(btnId == PLUS){
              Serial.println("STEPS \t| Plus pressed");   //steps randomize or somehow control steps
            }
            else if(btnId == MINUS){                      // type - trig->random, trig->next, V/OCT steps,
              if(AselectedStrip == STRIP_BOTH){
                stripXdata.reaction++;
                if(stripXdata.reaction > 3){
                  stripXdata.reaction = 0;
                }
                stripYdata.reaction = stripXdata.reaction;
                Serial.print("STEPS \t| Reaction set for A and Z to "); Serial.println(stripXdata.reaction);
              }
              else if (AselectedStrip == STRIP_X){
                stripXdata.reaction++;
                if(stripXdata.reaction > 3){
                  stripXdata.reaction = 0;
                }
                Serial.print("STEPS \t| Reaction set for A to "); Serial.println(stripXdata.reaction);
              }
              else if (AselectedStrip == STRIP_Y){
                stripYdata.reaction++;
                if(stripYdata.reaction > 3){
                  stripYdata.reaction = 0;
                }
                Serial.print("STEPS \t| Reaction set for Z to "); Serial.println(stripYdata.reaction);
              }
            }
            else if(btnId == SELECT){ //both /set for RGB strip A/ strip Z RGB
              AselectedStrip++;
              if(AselectedStrip > 2){
                AselectedStrip = 0;
              }
              Serial.print("STEPS \t| Selected strip "); Serial.println(AselectedStrip);
            }
          break;
        case JAM:
            if(btnId == MODE){
              //go to black or go from black
              //for now without any fade
              lightsOn = !lightsOn;
              Serial.println("JAM \t| Go to black");
            }
            else if(btnId == PLUS){
              //pause animation
              pauseAnimation = !pauseAnimation;
              Serial.println("JAM \t| Pause animation");
            }
            else if(btnId == MINUS){
              //next animation
              stripXdata.animationIndex++;
              stripYdata.animationIndex++;
              if(stripXdata.animationIndex > 7){
                stripXdata.animationIndex = 0;
              }
              if(stripYdata.animationIndex > 7){
                stripYdata.animationIndex = 0;
              }
              Serial.println("JAM \t| Next animation");
            }
            else if(btnId == SELECT){
              //invert all signals
              invertSignals = !invertSignals;
              Serial.println("JAM \t| Invert all signals");
            }
          break;
        case MIDI:
            if(btnId == MODE){
              Serial.println("MIDI \t| Mode pressed");
            }
            else if(btnId == PLUS){
              Serial.println("MIDI \t| Plus pressed");
            }
            else if(btnId == MINUS){
              Serial.println("MIDI \t| Minus pressed");
            }
            else if(btnId == SELECT){
              Serial.println("MIDI \t| Select pressed");
            }
          break;
  
        case STRIPS:
            if(btnId == MODE){
              Serial.println("STRIPS \t| Mode pressed"); //no function for now
              editBrightness = !editBrightness;
            }
            else if(btnId == PLUS){ //add pixel
              if(!editBrightness){
                updateStripLength(ADD,SselectedStrip);
              }
              else{ //set to edit brightness
                updateStripBrightness(ADD,SselectedStrip);
              }
            }
            else if(btnId == MINUS){
              if(!editBrightness){
                updateStripLength(SUBTRACT,SselectedStrip);
              }
              else{ //set to edit brightness
                updateStripBrightness(SUBTRACT,SselectedStrip);
              }
            }
            else if(btnId == SELECT){
              //select strip
              SselectedStrip++;
              if(SselectedStrip > 2){
                SselectedStrip = 0;
              }
              Serial.print("STRIPS \t| Selected strip "); Serial.println(SselectedStrip);
            }
          break;
        case CAL:
            if(btnId == MODE){
              Serial.println("CAL \t| Mode pressed");
            }
            else if(btnId == PLUS){
              Serial.println("CAL \t| Plus pressed");
            }
            else if(btnId == MINUS){
              Serial.println("CAL \t| Minus pressed");
            }
            else if(btnId == SELECT){
              Serial.println("CAL \t| Select pressed");
            }
          break;
        case SETUP:
            if(btnId == MODE){
              Serial.println("SETUP \t| Mode pressed");
              saveToEEPROM();
            }
            else if(btnId == PLUS){
              Serial.println("SETUP \t| Plus pressed");
            }
            else if(btnId == MINUS){
              Serial.println("SETUP \t| Minus pressed");
            }
            else if(btnId == SELECT){
              Serial.println("SETUP \t| Select pressed");
            }
          break;
      }     
  }
  updateLEDs();
}

void lpHandler(Button2& btn){
  uint16_t time = btn.wasPressedFor();
    if(btn.getID() == MODE || btn.getID() == PLUS){
      modeAndPlus--;
    }

    if(btn.getID() == MINUS || btn.getID() == SELECT){
      minusAndSelect--;
    }

    if(btn.getID() == MINUS || btn.getID() == PLUS){
      plusAndMinus--;
    }

    if(btn.getID() == MODE || btn.getID() == SELECT){
      modeAndSelect--;
    }
}

void lpDetectedHandler(Button2& btn){
  switch(btn.getID()){
    case MODE:
      modeAndPlus++;
      modeAndSelect++;
      if(modeAndPlus < 2 && modeAndSelect < 2){
        menuPage = DECAY;
      }
      break;
    case PLUS:
      modeAndPlus++;
      plusAndMinus++;
      if(modeAndPlus < 2 && plusAndMinus < 2){
        menuPage = GAIN;
      }
      break;
    case MINUS:
      minusAndSelect++;
      plusAndMinus++;
      if(minusAndSelect < 2 && plusAndMinus < 2){
        menuPage = STEPS;
      }
      break;
    case SELECT:
      minusAndSelect++;
      modeAndSelect++;
      if(minusAndSelect < 2 && modeAndSelect < 2){
        menuPage = JAM;
      }
      break;
    default:
      break;
  }
  if(modeAndPlus >= 2){
    menuPage = MIDI;
  }
  if(minusAndSelect >= 2){
    menuPage = STRIPS;
  }
  if(modeAndSelect >= 2){
    menuPage = SETUP;
  }
  if(plusAndMinus >= 2){
    menuPage = CAL;
  }
  Serial.print("Now you are in menu ");Serial.println(menuPage);
  updateLEDs();
}
