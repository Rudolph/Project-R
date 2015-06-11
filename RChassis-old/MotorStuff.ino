// should redo this to ramp speeds up/down
// also need to check for sudden reversal and stop motors first
void doMotors(){
  if(motorsOn){
    if(lMotorSpeed > 0){                        // pwm left motor forward
      analogWrite(lMotor1, lMotorSpeed);
      digitalWrite(lMotor2, LOW);
    }else if(lMotorSpeed == 0){                 // left motor brake
      digitalWrite(lMotor1, HIGH);
      digitalWrite(lMotor2, HIGH);
      lCount = 0;                               // reset encoder every stop
    }else{
      digitalWrite(lMotor1, LOW);               // left motor reverse
      analogWrite(lMotor2, abs(lMotorSpeed));
    }
  
    if(rMotorSpeed > 0){
      analogWrite(rMotor1, rMotorSpeed);
      digitalWrite(rMotor2, LOW);
    }else if(rMotorSpeed == 0){
      digitalWrite(rMotor1, HIGH);
      digitalWrite(rMotor2, HIGH);
      rCount = 0;
    }else{
      digitalWrite(rMotor1, LOW);
      analogWrite(rMotor2, abs(rMotorSpeed));
    }
  }
}

void stopMotors(){
  if(motorsOn){
    lMotorSpeed = 0;
    rMotorSpeed = 0;
    doMotors();
  }
}

void disableMotors(){
  stopMotors();
  digitalWrite(nSleep, LOW);
  motorsOn = 0;
}

void enableMotors(){
  digitalWrite(nSleep, HIGH);
  motorsOn = 1;
}

