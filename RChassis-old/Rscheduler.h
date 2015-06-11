#ifndef RSCHED_H
#define RSCHED_H

#include "Arduino.h"

#define MAXTASKS 10

// apparently to use struct it has to go in a header and be included early
struct Rtask {
  void (*task)(void);
  uint32_t repeat;
  uint32_t wait;
};

int addTask(void (*pointer)(void), uint32_t repeat, uint32_t wait=0);
void runSched(void);

#endif
