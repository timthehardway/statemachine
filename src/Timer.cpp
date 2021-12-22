#include "Timer.h"

Timer::Timer(uint16_t interval)
  : interval(interval)
  , time(0)
{
}

void Timer::updateTimer()
{
  time = millis();
}

bool Timer::timerExpired()
{
  if (millis() - time > interval) return true;
  else return false;
}