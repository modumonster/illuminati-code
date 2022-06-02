const uint8_t azCVPin = 28;
const uint8_t rgCVPin = 27;
const uint8_t bpCVPin = 26;

const uint8_t azControlPin = 6;
const uint8_t rgControlPin = 7;
const uint8_t bpControlPin = 8;

uint16_t CVValues[6] = {0}; //soon to be deleted
double CVControls[6] = {0};


uint16_t Rmin = 190;
uint16_t Rmax = 3595;
uint16_t Gmin = 175;
uint16_t Gmax = 3602;
uint16_t Bmin = 178;
uint16_t Bmax = 3600;
uint16_t Pmin = 177;
uint16_t Pmax = 3597;
uint16_t Amin = 184;
uint16_t Amax = 3600;
uint16_t Zmin = 178;
uint16_t Zmax = 3605;


struct CV{
//  uint8_t readPin;
//  uint8_t switchPin;
//  uint8_t mySwitch;

  uint16_t rawValue;
  uint16_t rawLastValue;

  double   rangeMin;
  double   rangeMax;
  
  double   Value;
  uint16_t zeroVolts; //for calibration
  uint16_t fiveVolts; //for calibration
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
}


const bool readRBA = 0;
const bool readGPZ = 1;

bool CVswitch = readRBA;
void CVRead(){
  switch(CVswitch){
    case readRBA:
      CVValues[A] = analogRead(azCVPin);
      CVValues[R] = analogRead(rgCVPin);
      CVValues[B] = analogRead(bpCVPin);
      digitalWrite(azControlPin, HIGH);
      digitalWrite(rgControlPin, HIGH);
      digitalWrite(bpControlPin, HIGH);
      CVControls[R] = mapd(CVValues[R],Rmin,Rmax,-5,5);
      CVControls[B] = mapd(CVValues[B],Bmin,Bmax,-5,5);
      CVControls[A] = mapd(CVValues[A],Amin,Amax,-5,5);

      break;

    case readGPZ:  
      CVValues[Z] = analogRead(azCVPin);
      CVValues[G] = analogRead(rgCVPin);
      CVValues[P] = analogRead(bpCVPin);
      digitalWrite(azControlPin, LOW);
      digitalWrite(rgControlPin, LOW);
      digitalWrite(bpControlPin, LOW);
      CVControls[G] = mapd(CVValues[G],Gmin,Gmax,-5,5);
      CVControls[P] = mapd(CVValues[P],Pmin,Pmax,-5,5);
      CVControls[Z] = mapd(CVValues[Z],Zmin,Zmax,-5,5);

      break;
  }
    CVswitch = !CVswitch;
}

void CVReadNEW(){
  switch(CVswitch){
    case readRBA:
      rCV.rawValue = analogRead(rgCVPin);
      bCV.rawValue = analogRead(bpCVPin);
      aCV.rawValue = analogRead(azCVPin);
      digitalWrite(azControlPin, HIGH);
      digitalWrite(rgControlPin, HIGH);
      digitalWrite(bpControlPin, HIGH);
      rCV.Value = mapd(rCV.rawValue,rCV.fiveVolts-2*rCV.zeroVolts,rCV.fiveVolts,rCV.rangeMin,rCV.rangeMax);
      bCV.Value = mapd(bCV.rawValue,bCV.fiveVolts-2*bCV.zeroVolts,bCV.fiveVolts,bCV.rangeMin,bCV.rangeMax);
      aCV.Value = mapd(aCV.rawValue,aCV.fiveVolts-2*aCV.zeroVolts,aCV.fiveVolts,aCV.rangeMin,aCV.rangeMax);

      break;

    case readGPZ:  
      gCV.rawValue = analogRead(rgCVPin);
      pCV.rawValue = analogRead(bpCVPin);
      zCV.rawValue = analogRead(azCVPin);
      digitalWrite(azControlPin, LOW);
      digitalWrite(rgControlPin, LOW);
      digitalWrite(bpControlPin, LOW);
      gCV.Value = mapd(gCV.rawValue,gCV.fiveVolts-2*gCV.zeroVolts,gCV.fiveVolts,gCV.rangeMin,gCV.rangeMax);
      pCV.Value = mapd(pCV.rawValue,pCV.fiveVolts-2*pCV.zeroVolts,pCV.fiveVolts,pCV.rangeMin,pCV.rangeMax);
      zCV.Value = mapd(zCV.rawValue,zCV.fiveVolts-2*zCV.zeroVolts,zCV.fiveVolts,zCV.rangeMin,zCV.rangeMax);

      break;
  }
    CVswitch = !CVswitch;
}
void printCV(){
  Serial.print("R:"); Serial.print(CVValues[R]); Serial.print(" -> "); Serial.print(CVControls[R]); Serial.print("\t");
  Serial.print("G:"); Serial.print(CVValues[G]); Serial.print(" -> "); Serial.print(CVControls[G]); Serial.print("\t");
  Serial.print("B:"); Serial.print(CVValues[B]); Serial.print(" -> "); Serial.print(CVControls[B]); Serial.print("\t");
  Serial.print("P:"); Serial.print(CVValues[P]); Serial.print(" -> "); Serial.print(CVControls[P]); Serial.print("\t");
  Serial.print("A:"); Serial.print(CVValues[A]); Serial.print(" -> "); Serial.print(CVControls[A]); Serial.print("\t");
  Serial.print("Z:"); Serial.print(CVValues[Z]); Serial.print(" -> "); Serial.print(CVControls[Z]); Serial.println("\t");
}

void calibrateCV(){
  
  //bla bla bla, vyhodim data
  
}
