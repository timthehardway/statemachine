#ifndef SLAVE_SERIAL_H
#define SLAVE_SERIAL_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <string.h>

#define BUFLEN (10)
#define MESSAGE_START ('#')
#define MESSAGE_STOP (';')
#define MAX_TIME_FOR_REPLY (500)

class SlaveSerial {

typedef enum { WAITING_FOR_MESSAGE, READING_MESSAGE } CommunicationState;

private:
  uint8_t _rxPin;
  uint8_t _txPin;
  SoftwareSerial *serialConnection;
  char incomingMessage[BUFLEN];
  char buffer[BUFLEN];
  CommunicationState communicationState;
  
  void sendMessage(const char *message);
  bool addToIncomingMessage(char c);
  void clearIncomingMessage();

/*!
 * 
 * Send message to slave and get a valid reply.
 * @param message: message to be sent to slave.
 * @param buffer: buffer in which a reply is stored.
 * 
 * @return_bool: bool which indicates if slave replied with 'ACK'.
 * 
 * @pre: message and buffer may not be NULL.
*/
  bool sendMessageAndCheckReply(const char *message);
  int readIncomingMessage();

public:
  // SlaveSerial(uint8_t rxPin, uint8_t txPin);
  SlaveSerial(uint8_t rxPin, uint8_t txPin);
  ~SlaveSerial();
  void setup();
  void loop();

  bool sendBeat();
  bool switchToGreenAndGetReply();
  bool switchToRedAndGetReply();
};

#endif