#include "RP2040_PWM.h"
#include "RPi_Pico_TimerInterrupt.h"



#define TIMER0_INTERVAL_MS        1
RPI_PICO_Timer ITimer0(0);

bool TimerHandler0(struct repeating_timer *t)
{
  static bool toggle0 = false;

#if (TIMER_INTERRUPT_DEBUG > 0)
  Serial.print("ITimer0: millis() = "); Serial.println(millis());
#endif

  CVRead();
  CVtoLamp();
  CVtoStrip();
  LEDHandler();
  return true;
}


void setup(){
  Serial.begin(115200);
    // init interrupt
    if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another Timer, freq. or timer"));

    
  buttonInit();
  ledsInit();
  lampInit();
  stripsInit();
  CVInit();
      
}

void loop(){
  testbla();
  delay(1000);
}
