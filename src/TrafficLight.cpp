#include "trafficLight.h"

TrafficLight::TrafficLight() {}

void TrafficLight::setup(uint8_t greenLedPin, uint8_t redLedPin)
{
  _greenLedPin = greenLedPin;
  _redLedPin = redLedPin;

  pinMode(_greenLedPin, 1);
  pinMode(_redLedPin, 1);
  digitalWrite(_greenLedPin, 0);
  digitalWrite(_redLedPin, 0);

  setColor(RED);
}

void TrafficLight::loop() {}

void TrafficLight::setColor(TrafficLight::Color color)
{
  if (color == GREEN)
    {
        Serial.println("setColor(GREEN).");
        digitalWrite(_redLedPin, 0);
        digitalWrite(_greenLedPin, 1);
    }
    else
    {
        Serial.println("setColor(RED).");
        digitalWrite(_greenLedPin, 0);
        digitalWrite(_redLedPin, 1);
    }
}

void TrafficLight::setToGreen()
{
  setColor(GREEN);
}

void TrafficLight::setToRed()
{
  setColor(RED);
}