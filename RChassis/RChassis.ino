#include <MsTimer2.h>
#include <Servo.h>
#include "IOpins.h"
#include "Rscheduler.h"

/*
 * R(rrr) chassis
 *
 * 2014-07-06 v0.1
 *  added MsTimer2 dependency
 *  added simple scheduler
 * 2014-06-27 v0.0
 *  first go, setting things up and dialing in the encoders
 *
 */
volatile uint32_t lCount = 0;
volatile uint32_t rCount = 0;
volatile uint32_t tickCount = 0;

void setup(){
  pinMode(statusLED, OUTPUT);
  attachInterrupt(0, leftEnc, FALLING);
  attachInterrupt(1, rightEnc, FALLING);
  MsTimer2::set(10, doTicks); // set timer to update ticks every ten millis
  // add things to the scheduler, max 10 items
  // addTask(function, repeat, wait)

  
  MsTimer2::start();
  Serial.begin(115200);
}

void loop(){
  runSched();
}

void leftEnc(){
  lCount++;
}

void rightEnc(){
  rCount++;
}

void doTicks(){
  ++tickCount;
}

