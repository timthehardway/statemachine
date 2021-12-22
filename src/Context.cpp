#include "Context.h"

Context::Context()
  : _currentState (NULL)
  , _loadedStates ({ NULL })
  , _numOfStates (0)
{
}

Context::~Context() {}

void Context::setup(int numOfStates, int indexOfFirstState)
{
  _numOfStates = numOfStates;
  _currentState = _loadedStates[indexOfFirstState];
}



IState* Context::getState(TrafficLightState id)
{
  Serial.print("getState() is called with: ");Serial.println(id);

  for (int i = 0; i < _numOfStates; i++)
  {
    if (_loadedStates[i]->getId() == id)
    {
      Serial.print("State found on index: ");Serial.println(i);
      return _loadedStates[i];
    }
  }
  return nullptr;
}

void Context::run()
{
  _currentState->run(this);
}

void Context::setState(TrafficLightState state)
{
  _currentState = getState(state);
  Serial.print("////// CURRENT STATE NOW SET TO: ");Serial.println(_currentState->getId());
}

void Context::addState(IState* newState)
{
  if (_numOfStates < MAX_NR_OF_STATES) {
    _loadedStates[_numOfStates] = newState;
  }
  _numOfStates++;
  Serial.print("Number of states is now: ");Serial.println(_numOfStates);
}