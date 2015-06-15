#include <Wire.h>
#include <Servo.h>
#include "rudTasks.h"
#include "pindefs.h"

#define DEBUG

int lMotorSpeed = 0;
int rMotorSpeed = 0;
volatile uint32_t lCount = 0;
volatile uint32_t rCount = 0;
volatile uint32_t tickCount = 0;

Servo panServo;
Servo tiltServo;

// create the task manager thingie
rudTasks tasks(10);

void setup() {
  // setup encoders on interrupts with pullups enabled
  pinMode(lEnc, OUTPUT);
  digitalWrite(lEnc, HIGH);
  attachInterrupt(0, leftEnc, FALLING);
  pinMode(rEnc, OUTPUT);
  digitalWrite(rEnc, HIGH);
  attachInterrupt(1, rightEnc, FALLING);
  
  // setup motor control pins
  pinMode(lMotor1, OUTPUT);
  digitalWrite(lMotor1, LOW);
  pinMode(lMotor2, OUTPUT);
  digitalWrite(lMotor2, LOW);
  pinMode(rMotor1, OUTPUT);
  digitalWrite(rMotor1, LOW);
  pinMode(rMotor2, OUTPUT);
  digitalWrite(rMotor2, LOW);
  pinMode(lMotorSleep, OUTPUT);
  digitalWrite(lMotorSleep, LOW);  // drive low to sleep
  pinMode(rMotorSleep, OUTPUT);
  digitalWrite(rMotorSleep, LOW);
  pinMode(lMotorFault, INPUT);
  pinMode(rMotorFault, INPUT);
  digitalWrite(lMotorFault, HIGH);  // enable pullups on fault pins
  digitalWrite(rMotorFault, HIGH);  // cause they normally float and go low on fault
  
  // set up servos
  panServo.attach(headPan);
  tiltServo.attach(headTilt);
  // FIXME servo start/center positions should be stored in eeprom
  panServo.write(90);
  tiltServo.write(90);

  // add tasks here
  // tasks.add(functionToRun, int repeatInterval [int waitBeforeRun])

}

void loop() {
  // put your main code here, to run repeatedly:
  tasks.run();
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

