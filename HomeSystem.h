/*
  HomeSystem.h - Library for open-source home embedded system development.
  Created by RobotsInvented, March 17, 2016.
  Released into the public domain.
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

//char Str6[15] = "arduino";
class HomeSystem
{
    public:
      HomeSystem(char* userName); //
      void initialize();
      class homeSecurity
      {
        public:
          homeSecurity();//int pinCode);
          bool Arm(int pinCode);
          bool Disarm(int pinCode);
          bool getIsArmed();
          private:
            int userPinCode;
            bool m_isArmed;
      };
      class homeLight 
      {
        public:
          homeLight(int count);
          void turnLightOn(int lightNumber);
          void turnLightOff(int lightNumber);
          void switchOnAll();
          void switchOffAll();
      };
      class homeRemote
      {
        public:
          homeRemote(char bluetoothId[16]);
          int executeCommand(); //returns 0 if no command
          void sendFeedback(char feedbackMessage[64]); //send a message to the bluetooth serial output terminal
      };      
      homeSecurity homeSecurity;
      private:        
        char* m_userName;
};

#endif

