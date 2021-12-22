#ifndef ISTATE_H
#define ISTATE_H

#include "Context.h"
#include "Timer.h"
#include "TrafficLight.h"
#include "SlaveSerial.h"

class Context;

typedef enum {
  UNDEFINED,
  CONNECTING, 
  LIGHT_MASTER_GREEN, 
  LIGHT_SLAVE_GREEN,
  BOTH_LIGHTS_RED
} TrafficLightState;

class IState
{
  public:
    virtual void run(Context *context) = 0;
    virtual void setup(Timer* timer, TrafficLight* masterLight, SlaveSerial* slaveLight);
    virtual TrafficLightState getId();
    virtual ~IState() {};
};

#endif