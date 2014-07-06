#include <MsTimer2.h>
#include <Servo.h>
#include "pindefs.h"
#include "Rscheduler.h"

// various variables
int lMotorSpeed = 0;
int rMotorSpeed = 0;
int lMotorDir = 0; // 0=forward, 1=reverse
int rMotorDir = 0; // think of it as "yes, go backward now"

volatile uint32_t lCount = 0;
volatile uint32_t rCount = 0;
volatile uint32_t tickCount = 0;
volatile byte error = B0;

void setup(){
  pinMode(statusLED, OUTPUT);
  
  // set up the interrupts with pullup resistors enabled
  pinMode(lEnc, OUTPUT);
  digitalWrite(lEnc, HIGH);
  attachInterrupt(0, leftEnc, FALLING);
  pinMode(rEnc, OUTPUT);
  digitalWrite(rEnc, HIGH);
  attachInterrupt(1, rightEnc, FALLING);
  pinMode(nFault, OUTPUT);
  digitalWrite(nFault, HIGH);
  attachInterrupt(2, motorError, LOW);
  
  // set up the pins for motor control
  pinMode(lMotor1, OUTPUT);
  digitalWrite(lMotor1, LOW);
  pinMode(lMotor2, OUTPUT);
  digitalWrite(lMotor2, LOW);
  pinMode(rMotor1, OUTPUT);
  digitalWrite(rMotor1, LOW);
  pinMode(rMotor2, OUTPUT);
  digitalWrite(rMotor2, LOW);
  pinMode(nSleep, OUTPUT);
  digitalWrite(nSleep, LOW); // sleep motor drivers until they're wanted
  
  // set timer to update ticks every ten millis
  MsTimer2::set(10, doTicks);
  // add things to the scheduler, max 10 items
  // addTask(function, repeat[, wait])
  // where function is the function to run, repeat is when to run, 
  // and wait is how long to delay before running. repeat and wait
  // should be multiples of 10
  

  // get the timer going
  MsTimer2::start();
  // remove this after testing
  Serial.begin(115200);
}

void loop(){
  runSched();
}

void leftEnc(){
  if(lMotorDir){
    --lCount;
  }else{
    ++lCount;
  }
}

void rightEnc(){
  if(rMotorDir){
    --rCount;
  }else{
    ++rCount;
  }
}

void doTicks(){
  ++tickCount;
}

void motorError(){
  // stop motors FIXME
  // set error code
  error = B001;  
}
