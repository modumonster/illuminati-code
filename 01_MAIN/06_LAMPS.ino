const double lampPWMfreq = 100000.0; //Hz

RP2040_PWM* PWM_lampA;
RP2040_PWM* PWM_lampZ;

void lampInit(){
  PWM_lampA = new RP2040_PWM(A_LAMP_PIN, lampPWMfreq, 0.0);
  PWM_lampZ = new RP2040_PWM(Z_LAMP_PIN, lampPWMfreq, 0.0);

  if (PWM_lampA)
  {
    PWM_lampA->setPWM();
  }
  if (PWM_lampZ)
  {
    PWM_lampZ->setPWM();
  }
}


void printPWMInfo(RP2040_PWM* PWM_Instance)
{
  uint32_t div = PWM_Instance->get_DIV();
  uint32_t top = PWM_Instance->get_TOP();

  Serial.print("Actual PWM Frequency = "); Serial.println(PWM_Instance->getActualFreq());

  PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", PWM_Instance->get_freq_CPU());
}

uint8_t lastA = 0;
uint8_t lastZ = 0;
uint8_t valA;
uint8_t valZ;

void CVtoLamp(){
  if(lampALinear){
    valA = cie(toValue(A));
  }
  else{
    valA = map(toValue(A),0,255,0,100);
  }
  if(lastA != valA){
  PWM_lampA->setPWM(A_LAMP_PIN, lampPWMfreq, valA, true);
    lastA = valA;
  }
  if(lampZLinear){
    valZ = cie(toValue(Z));
  }
  else{
    valZ = map(toValue(Z),0,255,0,100);
  }
  if(lastZ != valZ){
    PWM_lampZ->setPWM(Z_LAMP_PIN, lampPWMfreq, valZ, true);
    lastZ = valZ;
  }
}

double dutyA = 50.0;
double dutyZ = 50.0;

void testLamp(){
  for(dutyA = 0.0; dutyA <= 100.0; dutyA = dutyA+0.1){
    PWM_lampA->setPWM(A_LAMP_PIN, lampPWMfreq, dutyA, true);
    dutyZ = dutyA;
    PWM_lampZ->setPWM(Z_LAMP_PIN, lampPWMfreq, dutyZ, true);
    delay(10);
  }
}
