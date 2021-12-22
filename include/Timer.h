#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer
{
  private:
    unsigned long time;
    uint16_t interval;

  public:
    Timer(uint16_t interval);
    void updateTimer();
    bool timerExpired();
};

#endif