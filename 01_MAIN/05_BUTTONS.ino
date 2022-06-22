const uint16_t debounceMillis = 5;
const uint16_t longPressMillis = 500;

Button2 btnMode, btnPlus, btnMinus, btnSelect;

void buttonInit(){
  btnMode.begin(BmodePin);
  btnPlus.begin(BplusPin);
  btnMinus.begin(BminusPin);
  btnSelect.begin(BselectPin);
  
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



uint8_t modeAndPlus = 0;
uint8_t minusAndSelect = 0;


void clickHandler(Button2& btn){
  if (btn.getType() == single_click) {        
    uint8_t btnId = btn.getID();
      switch(menuPage){
        case GAIN:
            if(btnId == MODE){
              //for now no function
              Serial.println("GAIN\t| Mode pressed");
            }
            else if(btnId == PLUS){     //-5/-2.5/-0 minimum voltage
              CV[GselectedCV].minIndex++;
              if(CV[GselectedCV].minIndex > 2){
                CV[GselectedCV].minIndex = 0;
              }              
              Serial.print("GAIN\t| Min of CV ");Serial.print(GselectedCV); Serial.print(" set to "); Serial.println(CV[GselectedCV].minIndex);
            }
            else if(btnId == MINUS){    //5/2.5/0 maximum voltage
              CV[GselectedCV].maxIndex++;
              if(CV[GselectedCV].maxIndex > 2){
                CV[GselectedCV].maxIndex = 0;
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
              //for now no use
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
        case STEPS: //should be probably renamed to something like animation/program
            if(btnId == MODE){
              Serial.println("STEPS \t| Mode pressed");
            }
            else if(btnId == PLUS){
              //steps randomize or somehow control steps
              Serial.println("STEPS \t| Plus pressed");
            }
            else if(btnId == MINUS){
              // type - trig->random, trig->next, V/OCT steps,
              if(AselectedStrip == STRIP_BOTH){
                strip_A.reaction = strip_A.reaction;
                strip_A.reaction++;
                if(strip_A.reaction > 3){
                  strip_A.reaction = 0;
                }
                strip_Z.reaction = strip_A.reaction;
                Serial.print("STEPS \t| Reaction set for A and Z to "); Serial.println(strip_A.reaction);
              }
              else if (AselectedStrip == STRIP_A){
                strip_A.reaction++;
                if(strip_A.reaction > 3){
                  strip_A.reaction = 0;
                }
                Serial.print("STEPS \t| Reaction set for A to "); Serial.println(strip_A.reaction);
              }
              else if (AselectedStrip == STRIP_Z){
                strip_Z.reaction++;
                if(strip_Z.reaction > 3){
                  strip_Z.reaction = 0;
                }
                Serial.print("STEPS \t| Reaction set for Z to "); Serial.println(strip_Z.reaction);
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
              //go to black
              Serial.println("JAM \t| Go to black");
            }
            else if(btnId == PLUS){
              //pause animation
              Serial.println("JAM \t| Pause animation");
            }
            else if(btnId == MINUS){
              //next animation
              Serial.println("JAM \t| Next animation");
            }
            else if(btnId == SELECT){
              //invert all signals
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
              Serial.println("STRIPS \t| Mode pressed");
            }
            else if(btnId == PLUS){
              Serial.println("STRIPS \t| Plus pressed");
            }
            else if(btnId == MINUS){
              Serial.println("STRIPS \t| Minus pressed");
            }
            else if(btnId == SELECT){
              Serial.println("STRIPS \t| Select pressed");
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
}

void lpDetectedHandler(Button2& btn){
  switch(btn.getID()){
    case MODE:
      modeAndPlus++;
      if(modeAndPlus < 2){
        menuPage = DECAY;
      }
      break;
    case PLUS:
      modeAndPlus++;
      if(modeAndPlus < 2){
        menuPage = GAIN;
      }
      break;
    case MINUS:
      minusAndSelect++;
      if(minusAndSelect < 2){
        menuPage = STEPS;
      }
      break;
    case SELECT:
      minusAndSelect++;
      if(minusAndSelect < 2){
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
  Serial.print("Now you are in menu ");Serial.println(menuPage);
  updateLEDs();
}
