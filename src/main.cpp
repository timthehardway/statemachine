#include <Arduino.h>
#include <SoftwareSerial.h>
#include <string.h>

#include "TrafficLight.h"
#include "SlaveSerial.h"
#include "Timer.h"
#include "Context.h"
#include "States.h"

#define LIGHT_SWITCH_INTERVAL (1000)
#define MASTER_GREEN_LIGHT_PIN 3
#define MASTER_RED_LIGHT_PIN 4
#define SLAVE_SERIAL_RX_PIN 10
#define SLAVE_SERIAL_TX_PIN 11
#define NUM_OF_STATES 4

// Objects.
Timer timer(LIGHT_SWITCH_INTERVAL);
TrafficLight masterLight;
SlaveSerial slaveLight(SLAVE_SERIAL_RX_PIN, SLAVE_SERIAL_TX_PIN);
IState* stateConnecting = new StateConnecting;
IState* stateLightMasterGreen = new StateLightMasterGreen;
IState* stateLightSlaveGreen = new StateLightSlaveGreen;
IState* stateBothLightsRed = new StateBothLightsRed;
Context stateMachine;

void setup() {
  Serial.begin(9600);
  masterLight.setup(MASTER_GREEN_LIGHT_PIN, MASTER_RED_LIGHT_PIN);
  slaveLight.setup();

  stateConnecting->setup(&timer, &masterLight, &slaveLight);
  stateLightMasterGreen->setup(&timer, &masterLight, &slaveLight);
  stateLightSlaveGreen->setup(&timer, &masterLight, &slaveLight);
  stateBothLightsRed->setup(&timer, &masterLight, &slaveLight);

  stateMachine.addState(stateConnecting);
  stateMachine.addState(stateLightMasterGreen);
  stateMachine.addState(stateLightSlaveGreen);
  stateMachine.addState(stateBothLightsRed);

  stateMachine.setup(NUM_OF_STATES, 0);
}

void loop() {
  stateMachine.run();
}