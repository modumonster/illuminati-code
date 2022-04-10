const uint8_t modePin = 12;
const uint8_t plusPin = 13;
const uint8_t minusPin = 14;
const uint8_t selectPin = 15;

const uint8_t debounceTime = 100; //millis

#include <ezButton.h>

ezButton buttonMode(modePin);
ezButton buttonPlus(plusPin);
ezButton buttonMinus(minusPin);
ezButton buttonSelect(selectPin);

void buttonInit(){
  buttonMode.setDebounceTime(debounceTime);
  buttonPlus.setDebounceTime(debounceTime);
  buttonMinus.setDebounceTime(debounceTime);
  buttonSelect.setDebounceTime(debounceTime);
}

void buttonHandler(){
  buttonMode.loop();
  buttonPlus.loop();
  buttonMinus.loop();
  buttonSelect.loop();
  Serial.print("MODE:\t");Serial.print(buttonMode.getState());
  Serial.print("\t+:\t");Serial.print(buttonPlus.getState());
  Serial.print("\t-:\t");Serial.print(buttonMinus.getState());
  Serial.print("\tSELECT:\t");Serial.println(buttonSelect.getState());
}

/*
 * ### LEDs
*/

const uint8_t bluePin    = 22;
const uint8_t greenPin  = 21;
const uint8_t redPin = 20;
const uint8_t modeLed = 19;
const uint8_t plusLed = 18;
const uint8_t minusLed = 17;
const uint8_t selectLed = 16;


void ledsInit(){
  pinMode(redPin,OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(modeLed, OUTPUT);
  pinMode(plusLed, OUTPUT);
  pinMode(minusLed, OUTPUT);
  pinMode(selectLed, OUTPUT);


}

void ledHandler(){

}
