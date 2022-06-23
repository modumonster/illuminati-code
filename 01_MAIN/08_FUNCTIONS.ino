#include "cie1931.hpp"

constexpr Cie1931<> cie1931;


uint8_t cie(uint16_t input){
  return cie1931[input];
}


double mapd(double x, double in_min, double in_max, double out_min, double out_max)
{
    double out = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    if(out > out_max) out = out_max;
    if(out < out_min) out = out_min;
    return out;
}
