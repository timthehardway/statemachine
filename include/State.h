#ifndef STATE_H
#define STATE_H

class Context;

// als de volgende twee includes andersom staan bouwt het programma niet.
// (met de fout 'TrafficLightState' has not been declared).
#include "Context.h"
#include "IState.h"


#include "Timer.h"
#include "TrafficLight.h"
#include "SlaveSerial.h"


class State : public IState
{
  protected:
    TrafficLightState _id;
    Timer *_timer;
    TrafficLight *_masterLight;
    SlaveSerial *_slaveLight;
    bool _enterMethodDone;

    virtual void enter() = 0;
    virtual void loop(Context* context) = 0;

  public:
    State();
    virtual ~State();
    void setup(Timer* timer, TrafficLight* masterLight, SlaveSerial* slaveLight) override;

    void run(Context* context) override;
    TrafficLightState getId() override;
};

#endif