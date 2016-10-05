/*
  HomeSystem.h - Library for open-source home embedded system development.
  Created by RobotsInvented, March 17, 2016.
  Released into the public domain.
*/
#ifndef HomeSystem_h
#define HomeSystem_h

#include "Arduino.h"
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>


#define MAIN_DOOR 6
#define TABLE_LAMP 4
//char Str6[15] = "arduino";

class HomeSystem
{
    public:
      HomeSystem(char* userName1, char* userName2); //
      void initialize();
      class homeSecurity
      {
        public:
          homeSecurity();//int pinCode);
          void initialize();
          void process();
          char* getUserName1();
          char* getUserName2();
          bool arm(int pinCode);
          bool disarm(int pinCode);
          void lockDoor(int door);
          void unlockDoor(int door);
          bool getIsArmed();
          char* m_userName1;
          char* m_userName2;
          private:
          int userPinCode;
          bool m_isArmed;
      };
      class homeLight 
      {
        public:
          homeLight();
          void process();
          void switchOn(int light);
          void switchOff(int light);
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
      homeLight homeLight;
      private:
};

#endif

