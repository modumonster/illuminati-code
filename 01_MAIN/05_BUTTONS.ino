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
                  selectLED = RED; //this is temporary, just to test menu
                }
                else if(btnId == PLUS){
                  selectLED = GREEN;
                }
                else if(btnId == MINUS){
                  selectLED = BLUE;
                }
                else if(btnId == SELECT){
                  selectLED = YELLOW;
                }
              break;
            case DECAY:
                if(btnId == MODE){

                }
                else if(btnId == PLUS){
                  
                }
                else if(btnId == MINUS){
                  
                }
                else if(btnId == SELECT){
                  
                }
              break;
            case STEPS:
                if(btnId == MODE){

                }
                else if(btnId == PLUS){
                  
                }
                else if(btnId == MINUS){
                  
                }
                else if(btnId == SELECT){
                  
                }
              break;
            case JAM:
                if(btnId == MODE){

                }
                else if(btnId == PLUS){
                  
                }
                else if(btnId == MINUS){
                  
                }
                else if(btnId == SELECT){
                  
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
  //else if double_click
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
      else{
        //go to JAM menu
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
  updatePage();
}
