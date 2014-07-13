#include <MsTimer2.h>
#include <Servo.h>
#include <Wire.h>
#include "pindefs.h"
#include "Rscheduler.h"

// various variables
int motorsOn = 0;
int lMotorSpeed = 0;
int rMotorSpeed = 0;

volatile uint32_t lCount = 0;
volatile uint32_t rCount = 0;
volatile uint32_t tickCount = 0;
volatile int error = 0;

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
  
  // set timer to update ticks every 10 millis
  // so 100 ticks per second, give or take...
  MsTimer2::set(10, doTicks);
  // add things to the scheduler, max 10 items
  // addTask(function, repeat[, wait])
  // where function is the function to run, repeat is when to run, 
  // and wait is how long to delay before running.
  addTask(doMotors, 5); // every 5 ticks, 50 millis, 20 times per second
  addTask(doBlink, 50); // every 50 ticks, 500 millis, 2 times per second

  // get the timer going
  MsTimer2::start();
  
  // FIXME get from eeprom or 42
  Wire.begin(42);
  Wire.onReceive(getWire);
  Wire.onRequest(putWire);
  
  // remove this after testing
  Serial.begin(115200);
  Serial.println("Ready...");
}

void loop(){
  runSched();
}

void leftEnc(){
  if(lMotorSpeed > 0) ++lCount;
  if(lMotorSpeed < 0) --lCount;
}

void rightEnc(){
  if(rMotorSpeed > 0) ++rCount;
  if(rMotorSpeed < 0) --rCount;
}

void doTicks(){
  ++tickCount;
}

void motorError(){
  // stop motors
  // set error code
  stopMotors();
  disableMotors();
  error = 1;  
}

void doBlink(){
  static byte myblink = 0;
  myblink ^= 1;
  digitalWrite(statusLED, myblink);
}
