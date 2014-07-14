RChassis
----------

Chassis code for [Ruprecht the Rudforce Research Robot](http://hackaday.io/project/1615-Project-R)

Uses [mighty1284p](https://github.com/JChristensen/mighty-1284p) to put arduino stuff on an ATmega1284p

Requires Paul Stoffregen's [MsTimer2 library](https://github.com/PaulStoffregen/MsTimer2) (or [my version](https://github.com/Rudolph/MsTimer2) tweaked to work on the '1284) to handle the timing of the scheduler.

License is yet to be determined, but it'll definitely be open source. I'm leaning toward MIT I think, unless some other library or something forces the GPL on me.

----------

##I2C Commands
Defaults to address 42 (0x54)

* 0x45 - (E or 69)
  * E for Enable, followed by a 0 or 1 to disable or enable, respectively
* 0x4C - (L or 76)
  * L for Left Motor Speed, followed by -255 to 255 or 0 for brake
* 0x52 - (R or 82)
  * R for Right Motor Speed, followed by -255 to 255 or 0 for brake
* 0x42 - (B or 66)
  * B for Both Motors Speed, followed by -255 to 255 or 0 for brake

* 0x50 - (P or 80)*
  * P for Pan Servo followed by int
  * if int is 0-180 assume degrees, > ~700 assume microseconds
* 0x54 - (T or 84)*
  * T for Tilt Servo followed by int
  * if int is 0-180 assume degrees, > ~700 assume microseconds

* 0x44 - (D or 68)*
  * D for Default, followed by
    * 0x50 - (P or 80) for Pan servo center followed by int
    * 0x54 - (T or 84) for Tilt servo center followed by int
    * 0x49 - (I or 73) I for I2C address followed by int new address

`* not yet implemented`

##ToDo
"drive for X encoder clicks"
get/set I2C address, servo centers, from/to EEPROM
devise status packet to master, including encoder counts, error, etc...
rework encoder count reset and when
add servo stuff
check (read "proper test") assembly of 2 bytes into signed int for motor speed
