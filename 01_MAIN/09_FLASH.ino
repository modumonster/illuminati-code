#define MIN_INDEX_ADDR 0
#define MAX_INDEX_ADDR 1
#define RISE_TIME_ADDR 2
#define FALL_TIME_ADDR 3
#define P0_A_ADDR 4
#define P0_B_ADDR 5
#define P5_A_ADDR 6
#define P5_B_ADDR 7

#define NEXT_CV_OFFSET 8

void EEPROMInit(){
  EEPROM.begin(512);
  readEEPROM();
}

void updateEEPROM(uint16_t addr, uint8_t offset, uint8_t value){
  if(EEPROM.read(addr+offset*NEXT_CV_OFFSET) !=  value){
      EEPROM.write(addr+offset*NEXT_CV_OFFSET, value);
      Serial.print("Changed value in EEPROM ADDR "); Serial.print(addr+offset*NEXT_CV_OFFSET); Serial.print(" to "); Serial.println(value);
  }
}

void saveToEEPROM(){
  for(uint8_t i = 0; i < NUMBER_OF_CVS; i++){
    updateEEPROM(MIN_INDEX_ADDR,i,CV[i].minIndex);
    updateEEPROM(MAX_INDEX_ADDR,i,CV[i].maxIndex);
    updateEEPROM(RISE_TIME_ADDR,i,CV[i].riseTime);
    updateEEPROM(FALL_TIME_ADDR,i,CV[i].fallTime);
  }

  if (EEPROM.commit()) {
  Serial.println("EEPROM successfully committed");
  } else {
  Serial.println("ERROR! EEPROM commit failed");
  }
}

void readEEPROM(){
  Serial.println("Reading EEPROM");
    for(uint8_t i = 0; i < NUMBER_OF_CVS; i++){
      CV[i].minIndex = (EEPROM.read(MIN_INDEX_ADDR+i*NEXT_CV_OFFSET));
      CV[i].maxIndex = (EEPROM.read(MAX_INDEX_ADDR+i*NEXT_CV_OFFSET));
      CV[i].riseTime = (EEPROM.read(RISE_TIME_ADDR+i*NEXT_CV_OFFSET));
      CV[i].fallTime = (EEPROM.read(FALL_TIME_ADDR+i*NEXT_CV_OFFSET));
    }
}
