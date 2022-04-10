const uint8_t lampAPin = 10;
const uint8_t lampZPin = 11;

void lampInit(){
  pinMode(lampAPin,OUTPUT);
  pinMode(lampZPin,OUTPUT);
}

void testLamp(){
  digitalWrite(lampZPin,HIGH);
  delay(500);
  digitalWrite(lampZPin, LOW);
  delay(500);
}
