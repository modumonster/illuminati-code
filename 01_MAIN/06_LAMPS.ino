const double lampPWMfreq = 9000.0; //Hz
double dutyA = 50.0;
double dutyZ = 50.0;

RP2040_PWM* PWM_lampA;
RP2040_PWM* PWM_lampZ;

void lampInit(){
  PWM_lampA = new RP2040_PWM(lampAPin, lampPWMfreq, dutyA);
  PWM_lampZ = new RP2040_PWM(lampZPin, lampPWMfreq, dutyZ);

  if (PWM_lampA)
  {
    PWM_lampA->setPWM();
  }
  if (PWM_lampZ)
  {
    PWM_lampZ->setPWM();
  }

}
uint16_t lastA = 0;
uint16_t lastZ = 0;



void printPWMInfo(RP2040_PWM* PWM_Instance)
{
  uint32_t div = PWM_Instance->get_DIV();
  uint32_t top = PWM_Instance->get_TOP();

  Serial.print("Actual PWM Frequency = "); Serial.println(PWM_Instance->getActualFreq());

  PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", PWM_Instance->get_freq_CPU());
}

/*
void CVtoLamp(){
  if(lastA != CVValues[A]){
    double valA = mapd(CVValues[A],(Amin+Amax)/2,Amax,0,100);
  PWM_lampA->setPWM(lampAPin, lampPWMfreq, valA, true);
    lastA = CVValues[A];
    //printPWMInfo(PWM_lampA);
  }

  if(lastZ != CVValues[Z]){
    double valZ = mapd(CVValues[Z],(Zmin+Zmax)/2,Zmax,0,100);
    PWM_lampZ->setPWM(lampZPin, lampPWMfreq, valZ, true);
    lastZ = CVValues[Z];
  }
}

void testLamp(){
  for(dutyA = 0.0; dutyA <= 100.0; dutyA = dutyA+0.1){
    PWM_lampA->setPWM(lampAPin, lampPWMfreq, dutyA, true);
    dutyZ = dutyA;
    PWM_lampZ->setPWM(lampZPin, lampPWMfreq, dutyZ, true);
    delay(10);
  }
}
*/
