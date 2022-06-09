uint16_t CVValues[6] = {0}; //soon to be deleted
double CVControls[6] = {0};


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

#define R 0
#define G 1
#define B 2
#define P 3
#define A 4
#define Z 5

void CVInit(){
  analogReadResolution(12);
  pinMode(rgCVPin, INPUT);
  pinMode(bpCVPin, INPUT);
  pinMode(azCVPin, INPUT);
  pinMode(rgControlPin, OUTPUT);
  pinMode(bpControlPin, OUTPUT);
  pinMode(azControlPin, OUTPUT);

  digitalWrite(azControlPin, LOW);
  digitalWrite(rgControlPin, LOW);
  digitalWrite(bpControlPin, LOW);

 //for now, just measured data for calibration:
  rCV.p0 = 1890;
  rCV.p5 = 3595;

  gCV.p0 = 1889;
  gCV.p5 = 3602;

  bCV.p0 = 1949;
  bCV.p5 = 3600;

  pCV.p0 = 1888;
  pCV.p5 = 3597;

  aCV.p0 = 1891;
  aCV.p5 = 3600;

  zCV.p0 = 1893;
  zCV.p5 = 3605;

  calcRanges();
  
  rCV.rangeMin = rCV.p0;
  rCV.rangeMax = rCV.p5;

  gCV.rangeMin = gCV.m5;
  gCV.rangeMax = gCV.p5;

  bCV.rangeMin = bCV.m5;
  bCV.rangeMax = bCV.p5;

  pCV.rangeMin = pCV.m5;
  pCV.rangeMax = pCV.p5;

  aCV.rangeMin = aCV.m5;
  aCV.rangeMax = aCV.p5;

  zCV.rangeMin = zCV.m5;
  zCV.rangeMax = zCV.p5;
  printRanges();
}


const bool readRBA = 0;
const bool readGPZ = 1;

bool CVswitch = readRBA;

void calcVolts(){
  rCV.Volts = mapd(rCV.rawValue,rCV.m5,rCV.p5,-5,5);
  gCV.Volts = mapd(gCV.rawValue,gCV.m5,gCV.p5,-5,5);
  bCV.Volts = mapd(bCV.rawValue,bCV.m5,bCV.p5,-5,5);
  pCV.Volts = mapd(pCV.rawValue,pCV.m5,pCV.p5,-5,5);
  aCV.Volts = mapd(aCV.rawValue,aCV.m5,aCV.p5,-5,5);
  zCV.Volts = mapd(zCV.rawValue,zCV.m5,zCV.p5,-5,5);
}

void calcRanges(){ //for now done this stupidly, but I am afraid of pointers hehe
  rCV.m5 = 2*rCV.p0-rCV.p5;
  rCV.m2p5 = rCV.p0-((rCV.p5 - rCV.p0)*0.5);
  rCV.p2p5 = rCV.p5 - ((rCV.p5 - rCV.p0)*0.5);

  gCV.m5 = 2*gCV.p0-gCV.p5;
  gCV.m2p5 = gCV.p0-((gCV.p5 - gCV.p0)*0.5);
  gCV.p2p5 = gCV.p5 - ((gCV.p5 - gCV.p0)*0.5);

  bCV.m5 = 2*bCV.p0-bCV.p5;
  bCV.m2p5 = bCV.p0-((bCV.p5 - bCV.p0)*0.5);
  bCV.p2p5 = bCV.p5 - ((bCV.p5 - bCV.p0)*0.5);

  pCV.m5 = 2*pCV.p0-pCV.p5;
  pCV.m2p5 = pCV.p0-((pCV.p5 - pCV.p0)*0.5);
  pCV.p2p5 = pCV.p5 - ((pCV.p5 - pCV.p0)*0.5);

  aCV.m5 = 2*aCV.p0-aCV.p5;
  aCV.m2p5 = aCV.p0-((aCV.p5 - aCV.p0)*0.5);
  aCV.p2p5 = aCV.p5 - ((aCV.p5 - aCV.p0)*0.5);

  zCV.m5 = 2*zCV.p0-zCV.p5;
  zCV.m2p5 = zCV.p0-((zCV.p5 - zCV.p0)*0.5);
  zCV.p2p5 = zCV.p5 - ((zCV.p5 - zCV.p0)*0.5);
}

void CVRead(){
  switch(CVswitch){
    case readRBA:
      rCV.rawValue = analogRead(rgCVPin);
      bCV.rawValue = analogRead(bpCVPin);
      aCV.rawValue = analogRead(azCVPin);
      digitalWrite(azControlPin, HIGH);
      digitalWrite(rgControlPin, HIGH);
      digitalWrite(bpControlPin, HIGH);
      rCV.Value = mapd(rCV.rawValue,rCV.rangeMin,rCV.rangeMax,0,255);
      bCV.Value = mapd(bCV.rawValue,bCV.rangeMin,bCV.rangeMax,0,255);
      aCV.Value = mapd(aCV.rawValue,aCV.rangeMin,aCV.rangeMax,0,255);

      break;

    case readGPZ:  
      gCV.rawValue = analogRead(rgCVPin);
      pCV.rawValue = analogRead(bpCVPin);
      zCV.rawValue = analogRead(azCVPin);
      digitalWrite(azControlPin, LOW);
      digitalWrite(rgControlPin, LOW);
      digitalWrite(bpControlPin, LOW);
      gCV.Value = mapd(gCV.rawValue,gCV.rangeMin,gCV.rangeMax,0,255);
      pCV.Value = mapd(pCV.rawValue,pCV.rangeMin,pCV.rangeMax,0,255);
      zCV.Value = mapd(zCV.rawValue,zCV.rangeMin,zCV.rangeMax,0,255);

      break;
  }
    CVswitch = !CVswitch;
}
void printCV(){
  Serial.print("R:"); Serial.print(rCV.rawValue); Serial.print(" -> "); Serial.print(rCV.Value); Serial.print("\t");
  Serial.print("G:"); Serial.print(gCV.rawValue); Serial.print(" -> "); Serial.print(gCV.Value); Serial.print("\t");
  Serial.print("B:"); Serial.print(bCV.rawValue); Serial.print(" -> "); Serial.print(bCV.Value); Serial.print("\t");
  Serial.print("P:"); Serial.print(pCV.rawValue); Serial.print(" -> "); Serial.print(pCV.Value); Serial.print("\t");
  Serial.print("A:"); Serial.print(aCV.rawValue); Serial.print(" -> "); Serial.print(aCV.Value); Serial.print("\t");
  Serial.print("Z:"); Serial.print(zCV.rawValue); Serial.print(" -> "); Serial.print(zCV.Value); Serial.println("\t");
}

String x=" : "; //spacer

void printRanges(){
  Serial.print("R:\t"); Serial.println(rCV.m5+x+rCV.m2p5+x+rCV.p0+x+rCV.p2p5+x+rCV.p5); //+x just add " : " to the string
  Serial.print("G:\t"); Serial.println(gCV.m5+x+gCV.m2p5+x+gCV.p0+x+gCV.p2p5+x+gCV.p5);
  Serial.print("B:\t"); Serial.println(bCV.m5+x+bCV.m2p5+x+bCV.p0+x+bCV.p2p5+x+bCV.p5);
  Serial.print("P:\t"); Serial.println(pCV.m5+x+pCV.m2p5+x+pCV.p0+x+pCV.p2p5+x+pCV.p5);
  Serial.print("A:\t"); Serial.println(aCV.m5+x+aCV.m2p5+x+aCV.p0+x+aCV.p2p5+x+aCV.p5);
  Serial.print("Z:\t"); Serial.println(zCV.m5+x+zCV.m2p5+x+zCV.p0+x+zCV.p2p5+x+zCV.p5);
}

void printVolts(){
  calcVolts();
  Serial.print("R:"); Serial.print(rCV.Volts); Serial.print(" V");
  Serial.print("G:"); Serial.print(gCV.Volts); Serial.print(" V");
  Serial.print("B:"); Serial.print(bCV.Volts); Serial.print(" V");
  Serial.print("P:"); Serial.print(pCV.Volts); Serial.print(" V");
  Serial.print("A:"); Serial.print(aCV.Volts); Serial.print(" V");
  Serial.print("Z:"); Serial.print(zCV.Volts); Serial.print(" V");

}
void calibrateCV(){
  
  //bla bla bla, vyhodim data


  calcRanges();
}
