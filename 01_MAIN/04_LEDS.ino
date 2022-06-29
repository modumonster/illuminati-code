

const double ledPWMfreq = 40000.0; //Hz

#define BLINK_INTERVAL_MS 500

RP2040_PWM* PWM_ledR;
RP2040_PWM* PWM_ledG;
RP2040_PWM* PWM_ledB;

void ledsInit(){
  pinMode(RED_LED_PIN,OUTPUT);
  pinMode(GRN_LED_PIN, OUTPUT);
  pinMode(BLU_LED_PIN, OUTPUT);
  pinMode(MODE_LED_PIN, OUTPUT);
  pinMode(PLUS_LED_PIN, OUTPUT);
  pinMode(MNUS_LED_PIN, OUTPUT);
  pinMode(SLCT_LED_PIN, OUTPUT);

  PWM_ledR = new RP2040_PWM(RED_LED_PIN,    ledPWMfreq, 50.0);
  PWM_ledG = new RP2040_PWM(GRN_LED_PIN,  ledPWMfreq, 50.0);
  PWM_ledB = new RP2040_PWM(BLU_LED_PIN,   ledPWMfreq, 50.0);

  if (PWM_ledR) PWM_ledR->setPWM();
  if (PWM_ledG) PWM_ledG->setPWM();
  if (PWM_ledB) PWM_ledB->setPWM();

  digitalWrite(MODE_LED_PIN,  LOW);
  digitalWrite(PLUS_LED_PIN,  LOW);
  digitalWrite(MNUS_LED_PIN, LOW);
  digitalWrite(SLCT_LED_PIN,LOW);

  updateLEDs();
}

double rgbToDuty(uint8_t input){
  return 100.0-((double)input/255)*Lintensity;
}

uint8_t LHandlerState = 0;
uint16_t blinkCounter = 0;
bool blinkState = true;
void LEDHandler(){
  blinkCounter++;
  if(blinkCounter >= ((BLINK_INTERVAL_MS*1000)/TIMER1_INTERVAL_uS)){
    blinkState = !blinkState;
    blinkCounter = 0;
  }

  if(LHandlerState%2 == 0){
    PWM_ledR->setPWM(RED_LED_PIN,   ledPWMfreq, 100, true);
    PWM_ledG->setPWM(GRN_LED_PIN, ledPWMfreq, 100, true);
    PWM_ledB->setPWM(BLU_LED_PIN,  ledPWMfreq, 100, true);
  }
  else{
    LEDcolor setLEDColor;
    switch(LHandlerState){
    case 1:
      digitalWrite(SLCT_LED_PIN,  LOW);
      digitalWrite(MODE_LED_PIN,    HIGH);
      if(blinkState && blinkModeLED){
        setLEDColor = OFF;
      }
      else{
        setLEDColor = modeLED;
      }
      break;
    case 3:
      digitalWrite(MODE_LED_PIN,    LOW);
      digitalWrite(PLUS_LED_PIN,    HIGH);
      if(blinkState && blinkPlusLED){
        setLEDColor = OFF;
      }
      else{
        setLEDColor = plusLED;
      }
      break;
    case 5:
      digitalWrite(PLUS_LED_PIN,    LOW);
      digitalWrite(MNUS_LED_PIN,   HIGH);
      if(blinkState && blinkMinusLED){
        setLEDColor = OFF;
      }
      else{
        setLEDColor = minusLED;
      }
      break;
    case 7:
      digitalWrite(MNUS_LED_PIN,   LOW);
      digitalWrite(SLCT_LED_PIN,  HIGH);
      if(blinkState && blinkSelectLED){
        setLEDColor = OFF;
      }
      else{
        setLEDColor = selectLED;
      }
      break;
    default:
      break;
    }
    PWM_ledR->setPWM(RED_LED_PIN,   ledPWMfreq, rgbToDuty(setLEDColor.r), false);
    PWM_ledG->setPWM(GRN_LED_PIN, ledPWMfreq, rgbToDuty(setLEDColor.g), false);
    PWM_ledB->setPWM(BLU_LED_PIN,  ledPWMfreq, rgbToDuty(setLEDColor.b), false);
  }
  
  LHandlerState++;
  if(LHandlerState>7){
    LHandlerState = 0;
  }
}

void resetLEDs(){
  modeLED = OFF;
  plusLED = OFF;
  minusLED = OFF;
  selectLED = OFF;
}

void updateLEDs(){
  switch(menuPage){
    case GAIN:
      modeLED   = MENUcolor[GAIN];
      plusLED   = GAINMINcolor[CV[GselectedCV].minIndex];
      minusLED  = GAINMAXcolor[CV[GselectedCV].maxIndex];
      selectLED = CVcolor[GselectedCV];
      break;
    case DECAY:
      modeLED   = MENUcolor[DECAY];
      plusLED   = RFcolor[CV[DselectedCV].riseTime];
      minusLED  = RFcolor[CV[DselectedCV].fallTime];
      selectLED = CVcolor[DselectedCV];
      break;
    case STEPS:
      modeLED   = MENUcolor[STEPS];
      plusLED   = MENUcolor[STEPS]; //for now just same as STEPS
      if(AselectedStrip == STRIP_BOTH || AselectedStrip == STRIP_A){
        minusLED = REACTcolor[strip_A.reaction];
      }
      else{
        minusLED = REACTcolor[strip_Z.reaction];
      }
      selectLED = STRIPcolor[AselectedStrip];
      break;
    case JAM:
      modeLED   = MENUcolor[JAM];
      plusLED   = MENUcolor[JAM];
      minusLED  = MENUcolor[JAM];
      selectLED = MENUcolor[JAM];
      break;
    case MIDI:
      modeLED   = MENUcolor[MIDI];
      plusLED   = MENUcolor[MIDI];
      minusLED  = MENUcolor[MIDI];
      selectLED = MENUcolor[MIDI];
      break;
    case STRIPS:
      modeLED   = MENUcolor[STRIPS];
      plusLED   = MENUcolor[STRIPS];
      minusLED  = MENUcolor[STRIPS];
      selectLED = MENUcolor[STRIPS];
      break;
    case CAL:
      modeLED   = MENUcolor[CAL];
      plusLED   = MENUcolor[CAL];
      minusLED  = MENUcolor[CAL];
      selectLED = MENUcolor[CAL];
      break;
    case SETUP:
      modeLED   = MENUcolor[SETUP];
      plusLED   = MENUcolor[SETUP];
      minusLED  = MENUcolor[SETUP];
      selectLED = MENUcolor[SETUP];
      break;
  }
}

void ledTest(){
  modeLED = RED;
  delay(500);
  modeLED = GREEN;
  delay(500);
  modeLED = BLUE;
  delay(500);
  modeLED = OFF;
  delay(500);

  modeLED = OFF;
  plusLED = OFF;
  minusLED = OFF;
  selectLED = OFF;
  
  plusLED = RED;
  delay(500);
  plusLED = GREEN;
  delay(500);
  plusLED = BLUE;
  delay(500);
  plusLED = OFF;
  delay(500);

  minusLED = RED;
  delay(500);
  minusLED = GREEN;
  delay(500);
  minusLED = BLUE;
  delay(500);
  minusLED = OFF;
  delay(500);

  selectLED = RED;
  delay(500);
  selectLED = GREEN;
  delay(500);
  selectLED = BLUE;
  delay(500);
  selectLED = OFF;
  delay(500);
}
