#define NUMBER_OF_CVS 6

struct CVstruct{
  uint16_t rawValue;
  uint16_t avgValue = 0; //running average output
  uint16_t rawLastValue;

  //GAIN Min/Max
  uint8_t minIndex = 0; // 0->m5, 1->m2p5, 2->p0
  uint8_t maxIndex = 0; // 0->p5, 1->p2p5, 2->p0

  bool autoMin = false;
  bool autoMax = false;
  //DECAY times
  uint8_t riseTime = 0; // 0->0ms, 1->5ms, 2->10ms
  uint8_t fallTime = 0; // 0->0ms, 1->5ms, 2->10ms
    
  uint16_t p0;          //gathered from calibration
  uint16_t p5;          //gathered from calibration

  uint16_t m5;          //calculated from calibration (int for -5V)
  uint16_t m2p5;        //(int for -2.5V)
  uint16_t p2p5;

  uint16_t minimum = 65535;
  uint16_t maximum = 0;
};

const uint8_t rfTime[3] = {0,5,10}; //selectable rise/fall times [ms]

#define R 0
#define G 1
#define B 2
#define P 3
#define A 4
#define Z 5

CVstruct CV[NUMBER_OF_CVS];

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

const LEDcolor OFF      = {0,0,0};

const LEDcolor CVcolor[6]       = {RED,GREEN,BLUE,YELLOW,CYAN,MAGENTA};
const LEDcolor STRIPcolor[3]    = {RED,GREEN,BLUE};
const LEDcolor MENUcolor[8]     = {RED,GREEN,BLUE,YELLOW,CYAN,MAGENTA,OFF,OFF};
const LEDcolor RFcolor[3]       = {RED,GREEN,BLUE}; // 0ms, 5ms, 10ms
const LEDcolor GAINMINcolor[]   = {YELLOW,RED,GREEN,BLUE};
const LEDcolor GAINMAXcolor[]   = {YELLOW,RED,GREEN,BLUE};
const LEDcolor REACTcolor[4]    = {RED,GREEN,BLUE,YELLOW};

LEDcolor modeLED        = {0,0,0};
LEDcolor plusLED        = {0,0,0};
LEDcolor minusLED       = {0,0,0};
LEDcolor selectLED      = {0,0,0};

bool blinkModeLED    = false;
bool blinkPlusLED    = false;
bool blinkMinusLED   = false;
bool blinkSelectLED  = false;
//STRIPS

#define TRIG_RANDOM 0 //reaction to program signal
#define TRIG_NEXT   1
#define VOCT_STEPS  2
//animationIndex - index which corresponds to animation
#define RGB_ANIMATION 0

struct strip{
  uint8_t pixels = 16;

  uint8_t reaction; // TRIG_RANDOM, TRIG_NEXT, VOCT_STEPS (8 steps)
  uint8_t animationIndex = 0;
  uint8_t animations[8] = {0,1,2,3,4,5,6,7};

  uint8_t brightness = 50; //0-255
};

strip stripXdata;
strip stripYdata;

//MENU

#define GAIN    0
#define DECAY   1
#define STEPS   2
#define JAM     3
#define MIDI    4
#define STRIPS  5
#define CAL     6
#define SETUP   7

uint8_t menuPage = JAM;

// GAIN MENU
uint8_t GselectedCV = 0;
  //MODE - LINEAR/NONLINEAR BRIGHTNESS
  bool lampALinear = true;
  bool lampZLinear = true;

//DECAY MENU
uint8_t DselectedCV = 0;

//STEPS/ANIMATION/PROGRAM MENU
uint8_t AselectedStrip = 0;
#define STRIP_BOTH  0
#define STRIP_X     1
#define STRIP_Y     2

//JAM MENU
bool lightsOn = true;
bool pauseAnimation = false;
bool invertSignals = false;

//STRIPS MENU - setup strip pixels etc
uint8_t SselectedStrip = 0; //uses the same defines as AselectedStrip
#define ADD       1 //for updateStripLength function
#define SUBTRACT  -1
bool editBrightness = false;
