
void setup(){
  Serial.begin(9600);

  buttonInit();
  ledsInit();
  lampInit();
}

void loop(){
  buttonHandler();
  ledHandler();
  testLamp();
  stripATest();
}
