#include "Rscheduler.h"
/* contains functions for scheduler operations
 * 
 * 20140705 - first one
 */

// create the list o' tasks
Rtask tasks[MAXTASKS];

// called incessantly from loop() to run things what need running
void runSched(void){
  noInterrupts();
  
  while (tickCount){
    for (uint32_t i=0; i<MAXTASKS; i++){
      if (--tasks[i].wait == 0){
        tasks[i].wait = tasks[i].repeat;
        interrupts();
        tasks[i].task();
        noInterrupts();
      }
    }
    --tickCount;
  }
  
  interrupts();
}

// called in setup(), once for each function to schedule
// returns int just in case I wanna catch errors ever
int addTask (void (*pointer)(void), uint32_t repeat, uint32_t wait){
  static uint32_t schedCount = 0;
  if(schedCount < MAXTASKS){
    tasks[schedCount].task = pointer;
    tasks[schedCount].repeat = repeat;
    tasks[schedCount].wait = wait + 1;
    ++schedCount;
    return 0;
  }else{
    return -1;
  }
}
