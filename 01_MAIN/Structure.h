struct CVstruct{
  uint16_t rawValue;
  uint16_t rawLastValue;

  //GAIN Min/Max
  uint8_t minIndex = 0; // 0->m5, 1->m2p5, 2->p0
  uint8_t maxIndex = 0; // 0->p5, 1->p2p5, 2->p0
  
  //DECAY times
  uint8_t riseTime = 0; // 0->0ms, 1->5ms, 2->10ms
  uint8_t fallTime = 0; // 0->0ms, 1->5ms, 2->10ms
  
  double   Volts;
  double   Value;       //transformed from input using range to 0-255
  
  uint16_t p0;          //gathered from calibration
  uint16_t p5;          //gathered from calibration

  uint16_t m5;          //calculated from calibration (int for -5V)
  uint16_t m2p5;        //(int for -2.5V)
  uint16_t p2p5;
};

const uint8_t rfTime[3] = {0,5,10}; //selectable rise/fall times [ms]

#define R 0
#define G 1
#define B 2
#define P 3
#define A 4
#define Z 5

CVstruct CV[7];

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
const LEDcolor MENUcolor[7]     = {RED,GREEN,BLUE,YELLOW,CYAN,MAGENTA,OFF};
const LEDcolor RFcolor[3]       = {RED,GREEN,BLUE}; // 0ms, 5ms, 10ms
const LEDcolor GAINMINcolor[3]  = {RED,GREEN,BLUE};
const LEDcolor GAINMAXcolor[3]  = {RED,GREEN,BLUE};
const LEDcolor REACTcolor[4]    = {RED,GREEN,BLUE,YELLOW};

LEDcolor modeLED        = {0,0,0};
LEDcolor plusLED        = {0,0,0};
LEDcolor minusLED       = {0,0,0};
LEDcolor selectLED      = {0,0,0};

//STRIPS

#define TRIG_RANDOM 0 //reaction to program signal
#define TRIG_NEXT   1
#define VOCT_STEPS  2

struct strip{
  uint8_t pixels = 16;

  uint8_t reaction; // TRIG_RANDOM, TRIG_NEXT, VOCT_STEPS (8 steps)
  uint8_t steps[8] = {0,1,2,3,4,5,6,7};

  uint8_t intensity = 255; //0-255
};

strip strip_A;
strip strip_Z;

//MENU

#define GAIN 0
#define DECAY 1
#define STEPS 2
#define JAM 3
#define MIDI 4
#define STRIPS 5
#define CAL 6

uint8_t menuPage = JAM;

// GAIN MENU
uint8_t GselectedCV = 0;

//DECAY MENU
uint8_t DselectedCV = 0;

//STEPS/ANIMATION/PROGRAM MENU
uint8_t AselectedStrip = 0;
#define STRIP_BOTH  0
#define STRIP_A     1
#define STRIP_Z     2
