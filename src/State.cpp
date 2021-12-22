#include "State.h"

State::State()
  : _id (UNDEFINED)
  , _timer (NULL)
  , _masterLight (NULL)
  , _slaveLight (NULL)
  , _enterMethodDone (false)
{
}

State::~State() {}

void State::setup(Timer *timer, TrafficLight *masterLight, SlaveSerial *slaveLight)
{
  _timer = timer;
  _masterLight = masterLight;
  _slaveLight = slaveLight;

  Serial.print("State::setup() of: ");Serial.println(_id);
}

void State::run(Context* context)
{
  if (!_enterMethodDone) enter();
  loop(context);
}

TrafficLightState State::getId()
{
  return _id;
}