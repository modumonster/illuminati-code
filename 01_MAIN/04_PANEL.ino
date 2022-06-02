const uint8_t BmodePin = 12;
const uint8_t BplusPin = 13;
const uint8_t BminusPin = 14;
const uint8_t BselectPin = 15;

const uint8_t debounceTime = 100; //millis

#include <ezButton.h>

ezButton buttonMode(BmodePin);
ezButton buttonPlus(BplusPin);
ezButton buttonMinus(BminusPin);
ezButton buttonSelect(BselectPin);

void buttonInit(){
  buttonMode.setDebounceTime(debounceTime);
  buttonPlus.setDebounceTime(debounceTime);
  buttonMinus.setDebounceTime(debounceTime);
  buttonSelect.setDebounceTime(debounceTime);
}

void buttonHandler(){
  buttonMode.loop();
  buttonPlus.loop();
  buttonMinus.loop();
  buttonSelect.loop();
//  Serial.print("MODE:\t");Serial.print(buttonMode.getState());
//  Serial.print("\t+:\t");Serial.print(buttonPlus.getState());
//  Serial.print("\t-:\t");Serial.print(buttonMinus.getState());
//  Serial.print("\tSELECT:\t");Serial.println(buttonSelect.getState());
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
