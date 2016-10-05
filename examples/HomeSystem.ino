
//This Arduino Sketch is for RobotInvented's HomeSystem open-source embedded system development platform.
//Download a copy of this sketch at github.com/robotsInvented/homeSystem

#include "HomeSystem.h"

//"Eco Smart Home Security System" "RiseAbvHate_Eco_Smart_Home_Security_System"

HomeSystem homeSystem("Eco Smart Home Security System"); //"^Eco Smart Home Security System"

void setup() {
  // put your setup code here, to run once:
  homeSystem.initialize();
}

void loop() 
{
  // put your main code here, to run repeatedly:

  if(homeSystem.homeSecurity.getIsArmed() == true)
  {
    homeSystem.homeLight[TABLE_LAMP].switchOn();
  }
  else
  {
    homeSystem.homeLight[TABLE_LAMP].switchOff();
  }
}

