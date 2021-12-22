#ifndef STATES_H
#define STATES_H

#include "State.h"

class StateConnecting : public State
{
  private:
    void enter() override;
    void loop(Context *context) override;
    void exit();

  public:
    StateConnecting();
};

class StateLightMasterGreen : public State
{
  private:
    void enter() override;
    void loop(Context *context) override;
    void exit();

  public:
    StateLightMasterGreen();
};

class StateLightSlaveGreen : public State
{
  private:
    void enter() override;
    void loop(Context *context) override;
    void exit(Context *context);
  
  public:
    StateLightSlaveGreen();
};

typedef enum { MASTER, SLAVE } NextGreenLight;

class StateBothLightsRed : public State
{
  private:
    NextGreenLight _nextGreenLight;
    void enter() override;
    void loop(Context *context) override;
    void exit();
  
  public:
    StateBothLightsRed();
};

#endif