
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
  
  CV[R].rangeMin = CV[R].p0;
  CV[R].rangeMax = CV[R].p5;

  CV[G].rangeMin = CV[G].m5;
  CV[G].rangeMax = CV[G].p5;

  CV[B].rangeMin = CV[B].m5;
  CV[B].rangeMax = CV[B].p5;

  CV[P].rangeMin = CV[P].m5;
  CV[P].rangeMax = CV[P].p5;

  CV[A].rangeMin = CV[A].p0;
  CV[A].rangeMax = CV[A].p5;

  CV[Z].rangeMin = CV[Z].p0;
  CV[Z].rangeMax = CV[Z].p5;
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

void CVRead(){
  switch(CVswitch){
    case readRBA:
      CV[R].rawValue = analogRead(rgCVPin);
      CV[B].rawValue = analogRead(bpCVPin);
      CV[A].rawValue = analogRead(azCVPin);
      digitalWrite(azControlPin, HIGH);
      digitalWrite(rgControlPin, HIGH);
      digitalWrite(bpControlPin, HIGH);
      CV[R].Value = mapd(CV[R].rawValue,CV[R].rangeMin,CV[R].rangeMax,0,255);
      CV[B].Value = mapd(CV[B].rawValue,CV[B].rangeMin,CV[B].rangeMax,0,255);
      CV[A].Value = mapd(CV[A].rawValue,CV[A].rangeMin,CV[A].rangeMax,0,255);

      break;

    case readGPZ:  
      CV[G].rawValue = analogRead(rgCVPin);
      CV[P].rawValue = analogRead(bpCVPin);
      CV[Z].rawValue = analogRead(azCVPin);
      digitalWrite(azControlPin, LOW);
      digitalWrite(rgControlPin, LOW);
      digitalWrite(bpControlPin, LOW);
      CV[G].Value = mapd(CV[G].rawValue,CV[G].rangeMin,CV[G].rangeMax,0,255);
      CV[P].Value = mapd(CV[P].rawValue,CV[P].rangeMin,CV[P].rangeMax,0,255);
      CV[Z].Value = mapd(CV[Z].rawValue,CV[Z].rangeMin,CV[Z].rangeMax,0,255);

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

void nextMin(CVstruct &data)
{
  if(data.rangeMin == data.m5){
    data.rangeMin = data.m2p5;
  }
  else if (data.rangeMin == data.m2p5){
    data.rangeMin = data.p0;
  }
  else if (data.rangeMin == data.p0){
    data.rangeMin = data.m5;
  }
}


void nextMax(CVstruct &data)
{
  if(data.rangeMax == data.p0){
    data.rangeMax = data.p2p5;
    minusLED = RED;
  }
  else if (data.rangeMax == data.p2p5){
    data.rangeMax = data.p5;
    minusLED = GREEN;
  }
  else if (data.rangeMax == data.p5) {
    data.rangeMax = data.p0;
    minusLED = BLUE;
  }
}
