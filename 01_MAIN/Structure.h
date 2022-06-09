struct CV{
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

CV rCV, gCV, bCV, pCV, aCV, zCV;


/*
#define R 0
#define G 1
#define B 2
#define P 3
#define A 4
#define Z 5
*/



//MENU

#define GAIN 0
#define DECAY 1
#define STEPS 2
#define JAM 3
#define MIDI 4
#define STRIPS 5
#define CAL 6

uint8_t menuPage = JAM;
