
/*
 * ### LEDs
*/


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

const LEDcolor RED      = {255,0,0};
const LEDcolor GREEN    = {0,255,0};
const LEDcolor BLUE     = {0,0,255};

const LEDcolor YELLOW   = {255,255,0};
const LEDcolor CYAN     = {0,255,255};
const LEDcolor MAGENTA  = {255,0,255};

const LEDcolor OFF     = {0,0,0};

LEDcolor modeLED        = {0,0,0};
LEDcolor plusLED        = {0,0,0};
LEDcolor minusLED       = {0,0,0};
LEDcolor selectLED      = {0,0,0};

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

void resetLEDs(){
    modeLED = OFF;
    plusLED = OFF;
    minusLED = OFF;
    selectLED = OFF;
}
void ledTest(){
  modeLED = RED;
  delay(500);
  modeLED = GREEN;
  delay(500);
  modeLED = BLUE;
  delay(500);
  modeLED = OFF;

  plusLED = RED;
  delay(500);
  plusLED = GREEN;
  delay(500);
  plusLED = BLUE;
  delay(500);
  plusLED = OFF;

  minusLED = RED;
  delay(500);
  minusLED = GREEN;
  delay(500);
  modeLED = BLUE;
  delay(500);
  minusLED = OFF;

  selectLED = RED;
  delay(500);
  selectLED = GREEN;
  delay(500);
  selectLED = BLUE;
  delay(500);
  selectLED = OFF;
  
}
