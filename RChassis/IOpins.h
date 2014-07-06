// Pin Definitions
// left motor PWM
#define lMotor1  3
#define lMotor2  4

// right motor PWM
#define rMotor1  6
#define rMotor2  7

// pins for both motor drivers
#define nFault  2  // interrupt2
#define nSleep  5  // drive low to sleep

// wheel encoders, not that we address interrupts by pin number...
#define lEnc  10  // interrupt0
#define rEnc  11  // interrupt 1

// ACS711 current sensor
#define amps  A0
#define ampsFault  0

// the rest
#define statusLED  1

