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
                }
                else if(btnId == PLUS){     //-5/-2.5/-0 minimum voltage
                  nextMin(CV[GselectedCV]);
                }
                else if(btnId == MINUS){    //5/2.5/0 maximum voltage
                  nextMax(CV[GselectedCV]);
                }
                else if(btnId == SELECT){
                  GselectedCV++;
                  if(GselectedCV > 7){
                    GselectedCV = 0;
                  }
                }
              break;
            case DECAY:
                if(btnId == MODE){
                  //for now no use
                }
                else if(btnId == PLUS){
                  nextRising(CV[DselectedCV]);
                }
                else if(btnId == MINUS){
                  nextRising(CV[DselectedCV]);
                }
                else if(btnId == SELECT){
                  DselectedCV++;
                  if(DselectedCV > 7){
                    DselectedCV = 0;
                  }
                }
              break;
            case STEPS: //should be probably renamed to something like animation/program
                if(btnId == MODE){
                  
                }
                else if(btnId == PLUS){
                  //steps randomize or somehow control steps
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
                  }
                  else if (AselectedStrip == STRIP_A){
                    strip_A.reaction++;
                    if(strip_A.reaction > 3){
                      strip_A.reaction = 0;
                    }
                  }
                  else if (AselectedStrip == STRIP_Z){
                    strip_Z.reaction++;
                    if(strip_Z.reaction > 3){
                      strip_Z.reaction = 0;
                    }
                  }
                }
                else if(btnId == SELECT){ //both /set for RGB strip A/ strip Z RGB
                  AselectedStrip++;
                  if(AselectedStrip > 2){
                    AselectedStrip = 0;
                  }
                }
              break;
            case JAM:
                if(btnId == MODE){
                  //go to black
                }
                else if(btnId == PLUS){
                  //pause animation
                }
                else if(btnId == MINUS){
                  //next animation
                }
                else if(btnId == SELECT){
                  //invert all signals
                }
              break;
            case MIDI:
                if(btnId == MODE){

                }
                else if(btnId == PLUS){
                  
                }
                else if(btnId == MINUS){
                  
                }
                else if(btnId == SELECT){
                  
                }
              break;

            case STRIPS:
                if(btnId == MODE){

                }
                else if(btnId == PLUS){
                  
                }
                else if(btnId == MINUS){
                  
                }
                else if(btnId == SELECT){
                  
                }
              break;
            case CAL:
                if(btnId == MODE){

                }
                else if(btnId == PLUS){
                  
                }
                else if(btnId == MINUS){
                  
                }
                else if(btnId == SELECT){
                  
                }
              break;
          
          }
            
    Serial.print("click ");
    Serial.print("on button #");
    Serial.println(btn.getID());
}
}
void lpHandler(Button2& btn){
  uint16_t time = btn.wasPressedFor();
    if(btn.getID() == MODE || btn.getID() == PLUS) modeAndPlus--;

    if(btn.getID() == MINUS || btn.getID() == SELECT) minusAndSelect--;
}

void lpDetectedHandler(Button2& btn){
  switch(btn.getID()){

    case MODE || PLUS:
      break;
    case MODE:
      modeAndPlus++;
      if(modeAndPlus < 2){
        menuPage = DECAY;
        modeLED = GREEN;
      }
      break;
    case PLUS:
      modeAndPlus++;
      if(modeAndPlus < 2){
        menuPage = GAIN;
        modeLED = RED;
      }
      break;
    case MINUS:
      minusAndSelect++;
      if(minusAndSelect < 2){
        menuPage = STEPS;
        modeLED = BLUE;
      }
      break;
    case SELECT:
      minusAndSelect++;
      if(minusAndSelect < 2){
        menuPage = JAM;
        modeLED = YELLOW;
      }
      break;
    default:
      break;

  }
  if(modeAndPlus >= 2){
    menuPage = MIDI;
    modeLED = CYAN;
  }
  if(minusAndSelect >= 2){
    menuPage = STRIPS;
    modeLED = MAGENTA;
  }
}
