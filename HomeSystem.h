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
#include <SoftwareSerial.h>
//Credits to Keypad.h library

//homeSecurity pin configuration.
#define MAIN_DOOR 6

//homeLight pin configuration.
#define PIR_SENSOR 0
#define CEILING_LAMP 1
//#define TABLE_LAMP 0
//char Str6[15] = "arduino";

//homeRemote pin configuration.
#define RECEIVE 5
#define TRANSMIT 4

#define OPEN LOW
#define CLOSE HIGH

//Pot for LCD contrast:
//Voltage Vcc to V0 - 4.15V
//Voltage V0 to Gnd - 0.92V

class HomeSystem
{
    public:
      HomeSystem(String userName);
      void initialize();
      class homeSecurity
      {
        public:
          homeSecurity();//int pinCode);
          void initialize();
          void process();
          String getUserName1();
          String getUserName2();
          bool arm(int pinCode);
          bool disarm(int pinCode);
          void lockDoor(int door);
          void unlockDoor(int door);
          bool getIsArmed();
          String m_userName;
          private:
          int userPinCode;
          bool m_isArmed;
        private:
      };
      class homeLight 
      {
        public:
          homeLight();
          void initialize();
          void process();
          void switchOn(int light);
          void switchOff(int light);
          void switchOnAll();
          void switchOffAll();
      };
      class homeRemote
      {
        public:
          homeRemote();
          void initialize();
          void process();
          int executeCommand(String command); //returns 0 if no command
          void sendFeedback(String feedbackMessage); //send a message to the bluetooth serial output terminal
        private:
      };
      homeSecurity homeSecurity;
      homeLight homeLight;
      homeRemote homeRemote;
      private:
      String Id;
};

#endif

