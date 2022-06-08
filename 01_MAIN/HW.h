const uint8_t azCVPin = 28;
const uint8_t rgCVPin = 27;
const uint8_t bpCVPin = 26;

const uint8_t azControlPin = 6;
const uint8_t rgControlPin = 7;
const uint8_t bpControlPin = 8;

const uint8_t LredPin = 20;
const uint8_t LgreenPin  = 21;
const uint8_t LbluePin    = 22;

const uint8_t LmodePin = 19;
const uint8_t LplusPin = 18;
const uint8_t LminusPin = 17;
const uint8_t LselectPin = 16;


const uint8_t BmodePin = 12;
const uint8_t BplusPin = 13;
const uint8_t BminusPin = 14;
const uint8_t BselectPin = 15;

const uint8_t lampAPin = 10;
const uint8_t lampZPin = 11;

const uint8_t stripAPin = 2;
const uint8_t stripZPin = 3;




#define GAIN 0
#define DECAY 1
#define STEPS 2
#define JAM 3
#define MIDI 4
#define STRIPS 5
#define CAL 6

uint8_t menuPage = JAM;
