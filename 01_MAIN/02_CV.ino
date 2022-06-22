
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
  CV[R].p0 = 1890;
  CV[R].p5 = 3595;

  CV[G].p0 = 1889;
  CV[G].p5 = 3602;

  CV[B].p0 = 1949;
  CV[B].p5 = 3600;

  CV[P].p0 = 1888;
  CV[P].p5 = 3597;

  CV[A].p0 = 1891;
  CV[A].p5 = 3600;

  CV[Z].p0 = 1893;
  CV[Z].p5 = 3605;

  calcRanges();
  
  printRanges();
}


const bool readRBA = 0;
const bool readGPZ = 1;

bool CVswitch = readRBA;

void calcVolts(){
  CV[R].Volts = mapd(CV[R].rawValue,CV[R].m5,CV[R].p5,-5,5);
  CV[G].Volts = mapd(CV[G].rawValue,CV[G].m5,CV[G].p5,-5,5);
  CV[B].Volts = mapd(CV[B].rawValue,CV[B].m5,CV[B].p5,-5,5);
  CV[P].Volts = mapd(CV[P].rawValue,CV[P].m5,CV[P].p5,-5,5);
  CV[A].Volts = mapd(CV[A].rawValue,CV[A].m5,CV[A].p5,-5,5);
  CV[Z].Volts = mapd(CV[Z].rawValue,CV[Z].m5,CV[Z].p5,-5,5);
}

void calcRanges(){ //for now done this stupidly, but I am afraid of pointers hehe
  CV[R].m5 = 2*CV[R].p0-CV[R].p5;
  CV[R].m2p5 = CV[R].p0-((CV[R].p5 - CV[R].p0)*0.5);
  CV[R].p2p5 = CV[R].p5 - ((CV[R].p5 - CV[R].p0)*0.5);

  CV[G].m5 = 2*CV[G].p0-CV[G].p5;
  CV[G].m2p5 = CV[G].p0-((CV[G].p5 - CV[G].p0)*0.5);
  CV[G].p2p5 = CV[G].p5 - ((CV[G].p5 - CV[G].p0)*0.5);

  CV[B].m5 = 2*CV[B].p0-CV[B].p5;
  CV[B].m2p5 = CV[B].p0-((CV[B].p5 - CV[B].p0)*0.5);
  CV[B].p2p5 = CV[B].p5 - ((CV[B].p5 - CV[B].p0)*0.5);

  CV[P].m5 = 2*CV[P].p0-CV[P].p5;
  CV[P].m2p5 = CV[P].p0-((CV[P].p5 - CV[P].p0)*0.5);
  CV[P].p2p5 = CV[P].p5 - ((CV[P].p5 - CV[P].p0)*0.5);

  CV[A].m5 = 2*CV[A].p0-CV[A].p5;
  CV[A].m2p5 = CV[A].p0-((CV[A].p5 - CV[A].p0)*0.5);
  CV[A].p2p5 = CV[A].p5 - ((CV[A].p5 - CV[A].p0)*0.5);

  CV[Z].m5 = 2*CV[Z].p0-CV[Z].p5;
  CV[Z].m2p5 = CV[Z].p0-((CV[Z].p5 - CV[Z].p0)*0.5);
  CV[Z].p2p5 = CV[Z].p5 - ((CV[Z].p5 - CV[Z].p0)*0.5);
}


uint16_t rangeMin(CVstruct &data){
  uint16_t minimum;
  if(data.minIndex == 0){
    minimum = data.m5;
  }
  else if(data.minIndex == 1){
    minimum = data.m2p5;
  }
  else if(data.minIndex == 2){
    minimum = data.p0;
  }
  return minimum;
}

uint16_t rangeMax(CVstruct &data){
  uint16_t maximum;
  if(data.maxIndex == 0){
    maximum = data.p5;
  }
  else if(data.maxIndex == 1){
    maximum = data.p2p5;
  }
  else if(data.maxIndex == 2){
    maximum = data.p0;
  }
  return maximum;
}

void CVRead(){
  switch(CVswitch){
    case readRBA:
      CV[R].rawValue = analogRead(rgCVPin);
      CV[B].rawValue = analogRead(bpCVPin);
      CV[A].rawValue = analogRead(azCVPin);
      digitalWrite(azControlPin, HIGH);
      digitalWrite(rgControlPin, HIGH);
      digitalWrite(bpControlPin, HIGH);
      CV[R].Value = mapd(CV[R].rawValue,rangeMin(CV[R]),rangeMax(CV[R]),0,255);
      CV[B].Value = mapd(CV[B].rawValue,rangeMin(CV[B]),rangeMax(CV[B]),0,255);
      CV[A].Value = mapd(CV[A].rawValue,rangeMin(CV[A]),rangeMax(CV[A]),0,255);

      break;

    case readGPZ:  
      CV[G].rawValue = analogRead(rgCVPin);
      CV[P].rawValue = analogRead(bpCVPin);
      CV[Z].rawValue = analogRead(azCVPin);
      digitalWrite(azControlPin, LOW);
      digitalWrite(rgControlPin, LOW);
      digitalWrite(bpControlPin, LOW);
      CV[G].Value = mapd(CV[G].rawValue,rangeMin(CV[G]),rangeMax(CV[G]),0,255);
      CV[P].Value = mapd(CV[P].rawValue,rangeMin(CV[P]),rangeMax(CV[P]),0,255);
      CV[Z].Value = mapd(CV[Z].rawValue,rangeMin(CV[Z]),rangeMax(CV[Z]),0,255);

      break;
  }
    CVswitch = !CVswitch;
}
void printCV(){
  Serial.print("R:"); Serial.print(CV[R].rawValue); Serial.print(" -> "); Serial.print(CV[R].Value); Serial.print("\t");
  Serial.print("G:"); Serial.print(CV[G].rawValue); Serial.print(" -> "); Serial.print(CV[G].Value); Serial.print("\t");
  Serial.print("B:"); Serial.print(CV[B].rawValue); Serial.print(" -> "); Serial.print(CV[B].Value); Serial.print("\t");
  Serial.print("P:"); Serial.print(CV[P].rawValue); Serial.print(" -> "); Serial.print(CV[P].Value); Serial.print("\t");
  Serial.print("A:"); Serial.print(CV[A].rawValue); Serial.print(" -> "); Serial.print(CV[A].Value); Serial.print("\t");
  Serial.print("Z:"); Serial.print(CV[Z].rawValue); Serial.print(" -> "); Serial.print(CV[Z].Value); Serial.println("\t");
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
  calcVolts();
  Serial.print("R:"); Serial.print(CV[R].Volts); Serial.print(" V");
  Serial.print("G:"); Serial.print(CV[G].Volts); Serial.print(" V");
  Serial.print("B:"); Serial.print(CV[B].Volts); Serial.print(" V");
  Serial.print("P:"); Serial.print(CV[P].Volts); Serial.print(" V");
  Serial.print("A:"); Serial.print(CV[A].Volts); Serial.print(" V");
  Serial.print("Z:"); Serial.print(CV[Z].Volts); Serial.print(" V");

}
void calibrateCV(){
  
  //bla bla bla, vyhodim data

  calcRanges();
}
