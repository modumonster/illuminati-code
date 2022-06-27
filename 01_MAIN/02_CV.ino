void CVInit(){
  analogReadResolution(12);
  pinMode(RG_IN_PIN, INPUT);
  pinMode(BP_IN_PIN, INPUT);
  pinMode(AZ_IN_PIN, INPUT);
  pinMode(RG_CTRL_PIN, OUTPUT);
  pinMode(BP_CTRL_PIN, OUTPUT);
  pinMode(AZ_CTRL_PIN, OUTPUT);

  digitalWrite(AZ_CTRL_PIN, LOW);
  digitalWrite(RG_CTRL_PIN, LOW);
  digitalWrite(BP_CTRL_PIN, LOW);

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
double toValue(uint8_t index){
  return mapd(CV[index].rawValue,rangeMin(CV[index]),rangeMax(CV[index]),0,255);
}

double toVolts(uint8_t index){
  return mapd(CV[index].rawValue,CV[index].m5,CV[index].p5,-5,5);
}

void calcRanges(){ //need to do this better
  CV[R].m5    = 2*CV[R].p0 -   CV[R].p5;
  CV[R].m2p5  =   CV[R].p0 - ((CV[R].p5 - CV[R].p0)*0.5);
  CV[R].p2p5  =   CV[R].p5 - ((CV[R].p5 - CV[R].p0)*0.5);

  CV[G].m5    = 2*CV[G].p0 -   CV[G].p5;
  CV[G].m2p5  =   CV[G].p0 - ((CV[G].p5 - CV[G].p0)*0.5);
  CV[G].p2p5  =   CV[G].p5 - ((CV[G].p5 - CV[G].p0)*0.5);

  CV[B].m5    = 2*CV[B].p0 -   CV[B].p5;
  CV[B].m2p5  =   CV[B].p0 - ((CV[B].p5 - CV[B].p0)*0.5);
  CV[B].p2p5  =   CV[B].p5 - ((CV[B].p5 - CV[B].p0)*0.5);

  CV[P].m5    = 2*CV[P].p0 -   CV[P].p5;
  CV[P].m2p5  =   CV[P].p0 - ((CV[P].p5 - CV[P].p0)*0.5);
  CV[P].p2p5  =   CV[P].p5 - ((CV[P].p5 - CV[P].p0)*0.5);

  CV[A].m5    = 2*CV[A].p0 -   CV[A].p5;
  CV[A].m2p5  =   CV[A].p0 - ((CV[A].p5 - CV[A].p0)*0.5);
  CV[A].p2p5  =   CV[A].p5 - ((CV[A].p5 - CV[A].p0)*0.5);

  CV[Z].m5    = 2*CV[Z].p0 -   CV[Z].p5;
  CV[Z].m2p5  =   CV[Z].p0 - ((CV[Z].p5 - CV[Z].p0)*0.5);
  CV[Z].p2p5  =   CV[Z].p5 - ((CV[Z].p5 - CV[Z].p0)*0.5);
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
      CV[R].rawValue = analogRead(RG_IN_PIN);
      CV[B].rawValue = analogRead(BP_IN_PIN);
      CV[A].rawValue = analogRead(AZ_IN_PIN);
      digitalWrite(AZ_CTRL_PIN, HIGH);
      digitalWrite(RG_CTRL_PIN, HIGH);
      digitalWrite(BP_CTRL_PIN, HIGH);
      break;

    case readGPZ:  
      CV[G].rawValue = analogRead(RG_IN_PIN);
      CV[P].rawValue = analogRead(BP_IN_PIN);
      CV[Z].rawValue = analogRead(AZ_IN_PIN);
      digitalWrite(AZ_CTRL_PIN, LOW);
      digitalWrite(RG_CTRL_PIN, LOW);
      digitalWrite(BP_CTRL_PIN, LOW);
      break;
  }
  CVswitch = !CVswitch;
}
void printCV(){
  Serial.print("R:"); Serial.print(CV[R].rawValue); Serial.print(" -> "); Serial.print(toValue(R)); Serial.print("\t");
  Serial.print("G:"); Serial.print(CV[G].rawValue); Serial.print(" -> "); Serial.print(toValue(G)); Serial.print("\t");
  Serial.print("B:"); Serial.print(CV[B].rawValue); Serial.print(" -> "); Serial.print(toValue(B)); Serial.print("\t");
  Serial.print("P:"); Serial.print(CV[P].rawValue); Serial.print(" -> "); Serial.print(toValue(P)); Serial.print("\t");
  Serial.print("A:"); Serial.print(CV[A].rawValue); Serial.print(" -> "); Serial.print(toValue(A)); Serial.print("\t");
  Serial.print("Z:"); Serial.print(CV[Z].rawValue); Serial.print(" -> "); Serial.print(toValue(Z)); Serial.println("\t");
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
void calibrateCV(){
  
  //bla bla bla, vyhodim data

  calcRanges();
}
