/*
this needs to:
  enable/disable motors (1 or 0)
  set L motor speed
  set R motor speed
  set both motor speeds
  
  enable/disable servo n
  set servo n position
  set servo n default center to eeprom
  
  set I2C address to eeprom
*/
void getWire(int count){
  // read stuff
  byte b;
  int i;
  
  b = Wire.read();
  switch (b) {
    case 0x45:
      // 0 or 1
      i = Wire.read();
      if(i == 1){
        enableMotors();
      }else{
        disableMotors();
      }
      break;
    case 0x4C:
      // read int into lMotorSpeed
      i = (Wire.read() << 8) + Wire.read();
      if(i > -256 && i < 256){
        lMotorSpeed = i;
      }
      break;
    case 0x52:
      // read int into rMotorSpeed
      i = (Wire.read() << 8) + Wire.read();
      if(i > -256 && i < 256){
        rMotorSpeed = i;
      }
      break;
    case 0x42:
      // read int into both motor speeds
      i = (Wire.read() << 8) + Wire.read();
      if(i > -256 && i < 256){
        rMotorSpeed = i;
        lMotorSpeed = i;
      }
      doMotors();
      break;
    case 0x50:
      // read int into Pan servo position
      break;
    case 0x54:
      // read int into Tilt servo position
      break;
    case 0x44:
      // get next byte 0x50 then int
      // 0x54 then int
      // 0x49 then int
      break;
    default:
      break;
  }
}

/*
this needs to:
  send encoder counts (and reset them?)
  send ammeter value
*/
void putWire(){
  // say stuff
}
