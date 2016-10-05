//This Arduino Sketch is for RobotInvented's HomeSystem open-source embedded system development platform.
//Download a copy of this sketch at github.com/robotsInvented/homeSystem

#include "HomeSystem.h"

HomeSystem homeSystem("Eco Smart Home S", "ecurity System"); //RiseAbvHate

void setup() 
{
  homeSystem.initialize();
}

void loop() 
{
  
  homeSystem.homeSecurity.process();
  if(homeSystem.homeSecurity.getIsArmed() == true)
  {
    homeSystem.homeSecurity.lockDoor(MAIN_DOOR);
    homeSystem.homeLight.switchOff(TABLE_LAMP);
  }
  else
  {
    homeSystem.homeSecurity.unlockDoor(MAIN_DOOR);
    homeSystem.homeLight.switchOn(TABLE_LAMP);
  }
  homeSystem.homeLight.process();

}

