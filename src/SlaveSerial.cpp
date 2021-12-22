#include "SlaveSerial.h"

SlaveSerial::SlaveSerial(uint8_t rxPin, uint8_t txPin)
  : _rxPin(rxPin)
  , _txPin(txPin)
  , serialConnection(NULL)
  , incomingMessage({ '\0' })
  , buffer({ 0 })
  , communicationState(WAITING_FOR_MESSAGE)
{
}

SlaveSerial::~SlaveSerial()
{
  delete serialConnection;
}

void SlaveSerial::setup()
{
  serialConnection = new SoftwareSerial(_rxPin, _txPin);
  serialConnection->begin(9600);
}

void SlaveSerial::loop() {}

bool SlaveSerial::addToIncomingMessage(char c)
{
  // find position for next character.
  for (int i = 0; i < BUFLEN; i++) 
  {
    if (incomingMessage[i] == '\0') 
    {
      incomingMessage[i] = c;
      return true;
    }
  }
  return false;
}

void SlaveSerial::clearIncomingMessage()
{
  for (int i = 0; i < BUFLEN; i++)
  {
    incomingMessage[i] = '\0';
  }
}

void SlaveSerial::sendMessage(const char *message)
{
    serialConnection->print(MESSAGE_START);
    serialConnection->print(message);
    Serial.print("sendMessage() sent to slave: ");Serial.println(message);
    serialConnection->print(MESSAGE_STOP);
}

bool SlaveSerial::sendMessageAndCheckReply(const char *message)
{
  sendMessage(message);
  unsigned long timeStamp = millis();

  while (millis() - timeStamp < MAX_TIME_FOR_REPLY)
  {
    int messageReceived = readIncomingMessage();
    if (messageReceived == 1)
    {
      if (strcmp("ACK", buffer) == 0)
      {
        Serial.println("sendMessageAndCheckReply(): slave sent ACK, true is returned.");
        return 1;
      }
      else if (strcmp("NACK", buffer) == 0)
      {
        Serial.println("sendMessageAndCheckReply(): slave sent NACK, false is returned.");
        return 0;
      }
    }
    else if (messageReceived == -1)
    {
      Serial.println("sendMessageAndCheckReply(): error, false returned.");
      return 0;
    }
  }
  return 0; 
}

bool SlaveSerial::sendBeat()
{
  const char *beat = "BEAT";
  return sendMessageAndCheckReply(beat);
}

int SlaveSerial::readIncomingMessage()
{
    buffer[0] = '\0'; // lets clear the return c-string
    int rc = 0;// we start with no errors and nothing to return
    //
    // read the serial port buffer as long there are characters
    //
    while (serialConnection->available() > 0)
    {

        uint8_t incomingByte = serialConnection->read();

        // Serial.print((char)incomingByte);// lets debug a bit

        if (communicationState == WAITING_FOR_MESSAGE)
        {
            if (incomingByte == MESSAGE_START)
            {
                communicationState = READING_MESSAGE;
            }
        }
        else if (communicationState == READING_MESSAGE)
        {
            if (incomingByte == MESSAGE_STOP)
            {
                memcpy(buffer, incomingMessage, BUFLEN);
                clearIncomingMessage();
                Serial.println("////// incomingMessage cleaned!");
                communicationState = WAITING_FOR_MESSAGE;
                rc = 1;
            }
            else
            {
                if (!addToIncomingMessage(incomingByte))
                {
                  Serial.println("SlaveSerial::readIncomingMessage: adding char to incomingMessage failed!");
                }
            }
        }
    }// while-loop

    return rc; 
}

bool SlaveSerial::switchToGreenAndGetReply()
{
  const char *green = "GREEN";
  return sendMessageAndCheckReply(green);
}

bool SlaveSerial::switchToRedAndGetReply()
{
  const char *red = "RED";
  return sendMessageAndCheckReply(red);
}
