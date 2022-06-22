#include "RP2040_PWM.h"
#include "RPi_Pico_TimerInterrupt.h"

#include <Button2.h>
#include <Adafruit_NeoPixel.h>

#include "HW.h"
#include "Structure.h"

#define TIMER0_INTERVAL_uS 1000

RPI_PICO_Timer ITimer0(0);
RPI_PICO_Timer ITimer1(1);

bool TimerHandler0(struct repeating_timer *t)
{
  static bool toggle0 = false;

  CVRead();
  CVtoLamp();
  CVtoStrip();
  //printCV();
  return true;
}

bool TimerHandler1(struct repeating_timer *t)
{
  static bool toggle1 = false;

  LEDHandler();
  return true;
}


void setup() {
  Serial.begin(115200);

  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_uS, TimerHandler0);
  ITimer1.attachInterruptInterval(TIMER1_INTERVAL_uS, TimerHandler1);
  
  ledsInit();
  lampInit();
  stripsInit();
  CVInit();
  buttonInit();
}

void loop() {
  buttons();
}
