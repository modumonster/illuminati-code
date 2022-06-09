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


double mapd(double x, double in_min, double in_max, double out_min, double out_max)
{
    double out = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    if(out > out_max) out = out_max;
    if(out < out_min) out = out_min;
    return out;
}
