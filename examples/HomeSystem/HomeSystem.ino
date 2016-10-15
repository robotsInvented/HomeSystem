//This Arduino Sketch is for RobotInvented's HomeSystem open-source embedded system development platform.
//Download a copy of this sketch at github.com/robotsInvented/homeSystem/examples

#include <HomeSystem.h>

HomeSystem homeSystem("HomeSystem           Hello REMO ");

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
    homeSystem.homeLight.switchOff(CEILING_LAMP);
  }
  else
  {
    homeSystem.homeSecurity.unlockDoor(MAIN_DOOR);
    homeSystem.homeLight.switchOn(CEILING_LAMP);
  }
  homeSystem.homeRemote.process();
  //homeSystem.homeLight.process();

}

