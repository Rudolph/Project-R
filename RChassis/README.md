RChassis
=========

Chassis code for Ruprecht the Rudforce Research Robot
http://hackaday.io/project/1615-Project-R

Uses mighty1284p to put arduino stuff on an ATmega1284p
https://github.com/JChristensen/mighty-1284p

Requires Paul Stoffregen's MsTimer2 library
https://github.com/PaulStoffregen/MsTimer2
(my version tweaked to work on the 1284)
https://github.com/Rudolph/MsTimer2

License is yet to be determined, but it'll definitely be open source.
I'm leaning toward MIT I think, unless some other library or
something forces the GPL on me.

=========
##Commands

* 0x45 - (E or 69)
  * E for Enable, followed by a 0 or 1 to disable or enable, respectively
* 0x4C - (L or 76)
  * L for Left Motor Speed, followed by -255 to 255 or 0 for brake
* 0x52 - (R or 82)
  * R for Right Motor Speed, followed by -255 to 255 or 0 for brake
* 0x42 - (B or 66)
  * B for Both Motors Speed, followed by -255 to 255 or 0 for brake

* 0x50 - (P or 80)
  * P for Pan Servo followed by int microseconds
* 0x54 - (T or 84)
  * T for Tilt Servo followed by int microseconds

* 0x44 - (D or 68)
  * D for Default, followed by
    * 0x50 for Pan servo center followed by int microseconds
    * 0x54 for Tilt servo center followed by int microseconds
    * 0x49 (I or 73) I for I2C address followed by int new address




