/*
  HomeSystem.cpp - Library for flashing Morse code.
  Created by RobotsInvented, March 17, 2016.
  Released into the public domain.
*/

#include "Arduino.h"
#include "HomeSystem.h"

HomeSystem::HomeSystem(char* userName)
{
  m_userName = userName;
}

void HomeSystem::initialize()
{
  //LCD.print(userName);
  //Delay(3000);
  //blink led
  //play buzzer
}

HomeSystem::homeSecurity::homeSecurity()
{
  
}

bool HomeSystem::homeSecurity::getIsArmed()
{
  return m_isArmed;
}

