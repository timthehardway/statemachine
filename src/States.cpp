#include "States.h"

// StateConnecting

StateConnecting::StateConnecting()
  : State()
{
  _id = CONNECTING;
}

void StateConnecting::enter()
{
  _masterLight->setToRed();
  _enterMethodDone = true;

  Serial.println("StateConnecting::enter()");
}

void StateConnecting::loop(Context* context)
{
  if (_slaveLight->sendBeat() == true) {
    context->setState(LIGHT_MASTER_GREEN);
    exit();
  }
}

void StateConnecting::exit()
{
  Serial.println("StateConnecting::exit()");

  _enterMethodDone = false;
}


// StateLightMasterGreen

StateLightMasterGreen::StateLightMasterGreen()
  : State()
{
  _id = LIGHT_MASTER_GREEN;
}

void StateLightMasterGreen::enter()
{
  Serial.println("StateLightMasterGreen::enter()");

  if (_slaveLight->sendBeat() == true) {
    _masterLight->setToGreen();
    _timer->updateTimer();
  }

  _enterMethodDone = true;
}

void StateLightMasterGreen::loop(Context *context)
{
  if (_slaveLight->sendBeat() == false) {
    Serial.println("////// Am I triggered??");
    context->setState(CONNECTING);
  }

  if (_timer->timerExpired() == true) {
    context->setState(BOTH_LIGHTS_RED);
    exit();
  }
}

void StateLightMasterGreen::exit()
{
  Serial.println("StateLightMasterGreen::exit()");

  _masterLight->setToRed();
  _enterMethodDone = false;
}


// StateLightSlaveGreen

StateLightSlaveGreen::StateLightSlaveGreen()
  : State()
{
  _id = LIGHT_SLAVE_GREEN;
}

void StateLightSlaveGreen::enter()
{
  Serial.println("StateLightSlaveGreen::enter()");

  if (_slaveLight->switchToGreenAndGetReply() == true) {
    _timer->updateTimer();
  }
  _enterMethodDone = true;
}

void StateLightSlaveGreen::loop(Context *context)
{
  if (_slaveLight->sendBeat() == false) {
    context->setState(CONNECTING);
  }

  if (_timer->timerExpired() == true) {
    context->setState(BOTH_LIGHTS_RED);
    exit(context);
  }
}

void StateLightSlaveGreen::exit(Context *context)
{
  Serial.println("StateLightSlaveGreen::exit()");

  // make sure slaveLight acknowledged switch to red.
  if (_slaveLight->switchToRedAndGetReply() == false) {
    context->setState(CONNECTING);
  };
  _enterMethodDone = false;
}


// StateBothLightsRed

StateBothLightsRed::StateBothLightsRed()
  : State()
{
  _id = BOTH_LIGHTS_RED;
  _nextGreenLight = SLAVE;
}

void StateBothLightsRed::enter()
{
  Serial.println("StateBothLightsRed::enter()");

  _timer->updateTimer();
  _enterMethodDone = true;
}

void StateBothLightsRed::loop(Context* context)
{
  if (_slaveLight->sendBeat() == false) {
    context->setState(CONNECTING);
  }

  if (_timer->timerExpired() == true) {
    switch(_nextGreenLight) {
      case SLAVE:
        context->setState(LIGHT_SLAVE_GREEN);
        _nextGreenLight = MASTER;
        exit();
        break;
      case MASTER:
        context->setState(LIGHT_MASTER_GREEN);
        _nextGreenLight = SLAVE;
        exit();
        break;
      default:
        break;
    }
  }
}

void StateBothLightsRed::exit()
{
  Serial.println("StateBothLightsRed::exit()");
  _enterMethodDone = false;
}
