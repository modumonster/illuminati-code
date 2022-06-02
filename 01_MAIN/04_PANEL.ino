
const uint8_t BmodePin = 12;
const uint8_t BplusPin = 13;
const uint8_t BminusPin = 14;
const uint8_t BselectPin = 15;

const uint16_t longPressMillis = 1000;

Button2 buttonMode, buttonPlus, buttonMinus, buttonSelect;

void buttonInit(){
  buttonMode.begin(BmodePin);
  buttonPlus.begin(BplusPin);
  buttonMinus.begin(BminusPin);
  buttonSelect.begin(BselectPin);
  
  buttonMode.setClickHandler(clickHandler);
  buttonPlus.setClickHandler(clickHandler);
  buttonMinus.setClickHandler(clickHandler);
  buttonSelect.setClickHandler(clickHandler);

  buttonMode.setLongClickHandler(longpressHandler);
  buttonPlus.setLongClickHandler(longpressHandler);
  buttonMinus.setLongClickHandler(longpressHandler);
  buttonSelect.setLongClickHandler(longpressHandler);

  buttonMode.setLongClickDetectedHandler(lpDetectedHandler);
  buttonPlus.setLongClickDetectedHandler(lpDetectedHandler);
  buttonMinus.setLongClickDetectedHandler(lpDetectedHandler);
  buttonSelect.setLongClickDetectedHandler(lpDetectedHandler);
}

#define MODE    0
#define PLUS    1
#define MINUS   2
#define SELECT  3

void buttons(){
  buttonMode.loop();
  buttonPlus.loop();
  buttonMinus.loop();
  buttonSelect.loop();
}



uint8_t modeAndPlus = 0;
uint8_t minusAndSelect = 0;

void clickHandler(Button2& btn){
 switch (btn.getType()) {
        case single_click:
          
            switch(btn.getID()){
              case MODE:

                break;
              case PLUS:

                break;
              case MINUS:

                break;
              case SELECT:

                break;
              default:
                break;
            }
            
            break;
            
        case double_click:
            Serial.print("double ");
            break;
    }
    Serial.print("click ");
    Serial.print("on button #");
    Serial.println(btn.getID());
}
void longpressHandler(Button2& btn){
  uint16_t time = btn.wasPressedFor();
    if(btn.getID() == MODE || btn.getID() == PLUS) modeAndPlus--;

    if(btn.getID() == MINUS || btn.getID() == SELECT) minusAndSelect--;
}

void lpDetectedHandler(Button2& btn){

  switch(btn.getID()){
              case MODE:
                modeAndPlus++;
                if(modeAndPlus >= 2){
                  //go to MIDI menu
                }
                else{
                  
                }
                break;
              case PLUS:
                modeAndPlus++;
                if(modeAndPlus >= 2){
                  //go to MIDI menu
                }
                else{
                  //go to GAIN menu
                }
                break;
              case MINUS:
                minusAndSelect++;
                if(minusAndSelect >= 2){
                  //go to STRIPS menu
                }
                else{
                  //go to STEPS menu
                }
                break;
              case SELECT:
                minusAndSelect++;
                if(minusAndSelect >= 2){
                  //go to STRIPS menu
                }
                else{
                  //go to JAM menu
                }
                break;
              default:
                break;
            }

  //is there another button longpressed?
//  if()
}
/*
 * ### LEDs
*/


const uint8_t LredPin = 20;
const uint8_t LgreenPin  = 21;
const uint8_t LbluePin    = 22;

const uint8_t LmodePin = 19;
const uint8_t LplusPin = 18;
const uint8_t LminusPin = 17;
const uint8_t LselectPin = 16;

const double ledPWMfreq = 4000.0; //Hz
double dutyR = 100.0;
double dutyG = 100.0;
double dutyB = 100.0;
RP2040_PWM* PWM_ledR;
RP2040_PWM* PWM_ledG;
RP2040_PWM* PWM_ledB;

void ledsInit(){
  pinMode(LredPin,OUTPUT);
  pinMode(LgreenPin, OUTPUT);
  pinMode(LbluePin, OUTPUT);
  pinMode(LmodePin, OUTPUT);
  pinMode(LplusPin, OUTPUT);
  pinMode(LminusPin, OUTPUT);
  pinMode(LselectPin, OUTPUT);

  PWM_ledR = new RP2040_PWM(LredPin,    ledPWMfreq, 50.0);
  PWM_ledG = new RP2040_PWM(LgreenPin,  ledPWMfreq, 50.0);
  PWM_ledB = new RP2040_PWM(LbluePin,   ledPWMfreq, 50.0);

  if (PWM_ledR)PWM_ledR->setPWM();
  if (PWM_ledG)PWM_ledG->setPWM();
  if (PWM_ledB)PWM_ledB->setPWM();

  digitalWrite(LmodePin,  LOW);
  digitalWrite(LplusPin,  LOW);
  digitalWrite(LminusPin, LOW);
  digitalWrite(LselectPin,LOW);
}

struct LEDcolor{
  uint8_t r; //0-255
  uint8_t g;
  uint8_t b;
};

double Lintensity = 100.0;

const LEDcolor RED = {255,0,0};
const LEDcolor GREEN = {0,255,0};
const LEDcolor BLUE = {0,0,255};

LEDcolor modeLED = {255,0,0};
LEDcolor plusLED = {0,255,0};
LEDcolor minusLED = {0,0,255};
LEDcolor selectLED = {255,0,255};

double rgbToDuty(uint8_t input){
  return 100.0-((double)input/255)*Lintensity;
}

uint8_t LHandlerState = 0;
void LEDHandler(){
  switch(LHandlerState){
    case 0:
      digitalWrite(LselectPin,  LOW);
      digitalWrite(LmodePin,    HIGH);
      PWM_ledR->setPWM(LredPin,   ledPWMfreq, rgbToDuty(modeLED.r), true);
      PWM_ledG->setPWM(LgreenPin, ledPWMfreq, rgbToDuty(modeLED.g), true);
      PWM_ledB->setPWM(LbluePin,  ledPWMfreq, rgbToDuty(modeLED.b), true);
      break;
    case 1:
      digitalWrite(LmodePin,    LOW);
      digitalWrite(LplusPin,    HIGH);
      PWM_ledR->setPWM(LredPin,   ledPWMfreq, rgbToDuty(plusLED.r), true);
      PWM_ledG->setPWM(LgreenPin, ledPWMfreq, rgbToDuty(plusLED.g), true);
      PWM_ledB->setPWM(LbluePin,  ledPWMfreq, rgbToDuty(plusLED.b), true);
      break;
    case 2:
      digitalWrite(LplusPin,    LOW);
      digitalWrite(LminusPin,   HIGH);
      PWM_ledR->setPWM(LredPin,   ledPWMfreq, rgbToDuty(minusLED.r), true);
      PWM_ledG->setPWM(LgreenPin, ledPWMfreq, rgbToDuty(minusLED.g), true);
      PWM_ledB->setPWM(LbluePin,  ledPWMfreq, rgbToDuty(minusLED.b), true);
      break;
    case 3:
      digitalWrite(LminusPin,   LOW);
      digitalWrite(LselectPin,  HIGH);
      PWM_ledR->setPWM(LredPin,   ledPWMfreq, rgbToDuty(selectLED.r), true);
      PWM_ledG->setPWM(LgreenPin, ledPWMfreq, rgbToDuty(selectLED.g), true);
      PWM_ledB->setPWM(LbluePin,  ledPWMfreq, rgbToDuty(selectLED.b), true);
      break;
    default:
    break;
  }
  LHandlerState++;
  if(LHandlerState>3)LHandlerState = 0;
}


void ledTest(){
  
}
