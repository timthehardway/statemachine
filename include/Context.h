#ifndef CONTEXT_H
#define CONTEXT_H

class IState;

#include <Arduino.h>
#include <string.h>
#include "IState.h"

#define MAX_NR_OF_STATES 10

class Context
{
  private:
    IState* _currentState;
    IState* _loadedStates[MAX_NR_OF_STATES];
    int _numOfStates;

    IState* getState(TrafficLightState id);

  public:
    Context();
    ~Context();
    void setup(int numOfStates, int indexOfFirstState);
    void run();
    void setState(TrafficLightState state);
    void addState(IState* newState);
};

#endif