#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <Arduino.h>

class TrafficLight {

typedef enum { RED, GREEN } Color;

private:
  uint8_t _greenLedPin;
  uint8_t _redLedPin;
  void setColor(Color color);

public:
  TrafficLight();
  void setup(uint8_t greenLedPin, uint8_t redLedPin);
  void loop();
  
  void setToGreen();
  void setToRed();
};

#endif