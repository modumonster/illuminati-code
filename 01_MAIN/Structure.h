struct CVstruct{
//  uint8_t readPin;
//  uint8_t switchPin;
//  uint8_t mySwitch;

  uint16_t rawValue;
  uint16_t rawLastValue;

  double   rangeMin;
  double   rangeMax;
  
  double   Volts;
  
  double   Value;
  
  uint16_t p0; //gathered from calibration
  uint16_t p5; //gathered from calibration

  uint16_t m5; //calculated from calibration (int for -5V)
  uint16_t m2p5;  //(int for -2.5V)
  uint16_t p2p5;
  
};

#define R 0
#define G 1
#define B 2
#define P 3
#define A 4
#define Z 5

CVstruct CV[7];


//LEDs

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
uint8_t selectedCV = 0;
