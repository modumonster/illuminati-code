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


char s [80];
void printCV(){
  Serial.print("R:"); Serial.print(CV[R].rawValue); Serial.print(" -> "); Serial.print(CV[R].avgValue); Serial.print(" -> "); Serial.print(toValue(R)); Serial.print("\t");
  Serial.print("G:"); Serial.print(CV[G].rawValue); Serial.print(" -> "); Serial.print(CV[G].avgValue); Serial.print(" -> ");Serial.print(toValue(G)); Serial.print("\t");
  Serial.print("B:"); Serial.print(CV[B].rawValue); Serial.print(" -> "); Serial.print(CV[B].avgValue); Serial.print(" -> ");Serial.print(toValue(B)); Serial.print("\t");
  Serial.print("P:"); Serial.print(CV[P].rawValue); Serial.print(" -> "); Serial.print(CV[P].avgValue); Serial.print(" -> ");Serial.print(toValue(P)); Serial.print("\t");
  Serial.print("A:"); Serial.print(CV[A].rawValue); Serial.print(" -> "); Serial.print(CV[A].avgValue); Serial.print(" -> ");Serial.print(toValue(A)); Serial.print("\t");
  Serial.print("Z:"); Serial.print(CV[Z].rawValue); Serial.print(" -> "); Serial.print(CV[Z].avgValue); Serial.print(" -> ");Serial.print(toValue(Z)); Serial.println("\t");
}

void plotCV(){
  Serial.println("R:,Rsmooth:,G:,Gsmooth,B,Bsmooth,P,Psmooth,A,Asmooth,Z,Zsmooth");
  Serial.print(CV[R].rawValue);Serial.print(",");Serial.print(CV[R].avgValue);Serial.print(",");
  Serial.print(CV[G].rawValue);Serial.print(",");Serial.print(CV[G].avgValue);Serial.print(",");
  Serial.print(CV[B].rawValue);Serial.print(",");Serial.print(CV[B].avgValue);Serial.print(",");
  Serial.print(CV[P].rawValue);Serial.print(",");Serial.print(CV[P].avgValue);Serial.print(",");
  Serial.print(CV[A].rawValue);Serial.print(",");Serial.print(CV[A].avgValue);Serial.print(",");
  Serial.print(CV[Z].rawValue);Serial.print(",");Serial.print(CV[Z].avgValue);Serial.print(",");
}
String x=" : "; //spacer

void printRanges(){
  Serial.print("R:\t"); Serial.println(CV[R].m5+x+CV[R].m2p5+x+CV[R].p0+x+CV[R].p2p5+x+CV[R].p5); //+x just add " : " to the string
  Serial.print("G:\t"); Serial.println(CV[G].m5+x+CV[G].m2p5+x+CV[G].p0+x+CV[G].p2p5+x+CV[G].p5);
  Serial.print("B:\t"); Serial.println(CV[B].m5+x+CV[B].m2p5+x+CV[B].p0+x+CV[B].p2p5+x+CV[B].p5);
  Serial.print("P:\t"); Serial.println(CV[P].m5+x+CV[P].m2p5+x+CV[P].p0+x+CV[P].p2p5+x+CV[P].p5);
  Serial.print("A:\t"); Serial.println(CV[A].m5+x+CV[A].m2p5+x+CV[A].p0+x+CV[A].p2p5+x+CV[A].p5);
  Serial.print("Z:\t"); Serial.println(CV[Z].m5+x+CV[Z].m2p5+x+CV[Z].p0+x+CV[Z].p2p5+x+CV[Z].p5);
}

void printVolts(){
  Serial.print("R:"); Serial.print(toVolts(R)); Serial.print("V ");
  Serial.print("G:"); Serial.print(toVolts(G)); Serial.print("V ");
  Serial.print("B:"); Serial.print(toVolts(B)); Serial.print("V ");
  Serial.print("P:"); Serial.print(toVolts(P)); Serial.print("V ");
  Serial.print("A:"); Serial.print(toVolts(A)); Serial.print("V ");
  Serial.print("Z:"); Serial.print(toVolts(Z)); Serial.println("V ");

}
void printSettings(){
  Serial.println(" ========\t ALL SETTINGS \t ========");
  Serial.println("GAIN");
  Serial.print("\t MIN \t");Serial.println(CV[R].minIndex+x+CV[G].minIndex+x+CV[B].minIndex+x+CV[P].minIndex+x+CV[A].minIndex+x+CV[Z].minIndex);
  Serial.print("\t MAX \t");Serial.println(CV[R].maxIndex+x+CV[G].maxIndex+x+CV[B].maxIndex+x+CV[P].maxIndex+x+CV[A].maxIndex+x+CV[Z].maxIndex);
  Serial.println("DECAY");
  Serial.print("\t RISE \t");Serial.println(CV[R].riseTime+x+CV[G].riseTime+x+CV[B].riseTime+x+CV[P].riseTime+x+CV[A].riseTime+x+CV[Z].riseTime);
  Serial.print("\t FALL \t");Serial.println(CV[R].fallTime+x+CV[G].fallTime+x+CV[B].fallTime+x+CV[P].fallTime+x+CV[A].fallTime+x+CV[Z].fallTime);
}
