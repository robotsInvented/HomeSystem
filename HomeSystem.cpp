/*
  HomeSystem.cpp - Library for RobotsInvented's HomeSystem Open-Source Embedded System Development Platform.
  Created by RobotsInvented, March 17, 2016.
  Released into the public domain.
*/

#include "HomeSystem.h"

LiquidCrystal Lcd(7,8,9,10,11,12);
SoftwareSerial Bluetooth(4,5); // RX, TX
Servo Lock;

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {3,2,A5,A4}; //Rows 0 to 3
byte colPins[numCols]= {A3,A2,A1,A0}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

String command;
String message; //string that stores the incoming message

HomeSystem::HomeSystem(String userName)
{
  homeSecurity.m_userName = userName;
}

void HomeSystem::initialize()
{
  Serial.begin(9600); //set baud rate
  delay(50);
  homeSecurity.initialize();
  homeLight.initialize();
  homeRemote.initialize();
  Bluetooth.println("Home System Initialized");
  Serial.println("Home System Initialized");
}

HomeSystem::homeSecurity::homeSecurity()
{  
}

void HomeSystem::homeSecurity::initialize()
{
  tone(13,90);
  delay(95);
  noTone(13);
  delay(5);
  tone(13,15150);
  delay(100);
  noTone(13);
  
  Lcd.begin(16,2);
  Lcd.home();
  Lcd.print("homeSecurity");
  Serial.print("homeSecurity");
  delay(750);
  Lcd.clear();
  Lcd.print("homeSecurity.rob");
  Serial.println(".rob");
  Lcd.setCursor(0,1);
  Lcd.print("otsInvented");
  Serial.print("otsInvented");
  delay(750);
  Lcd.clear();
  Lcd.print("homeSecurity.rob");
  Lcd.setCursor(0,1);
  Lcd.print("otsInvented.asia");
  Serial.println(".asia");
  delay(3500);
  Lcd.clear();
  Lcd.home();
  Lcd.print(getUserName1());
  Lcd.setCursor(0,1);
  Lcd.print(getUserName2());
  
  Lock.attach(6);
  unlockDoor(MAIN_DOOR);
  
  Serial.println("homeSecurity Initialized");
  
  //Lcd.print(userName);
  //Delay(3000);
  //blink led
  //play buzzer
  
}

void HomeSystem::homeSecurity::process()
{
  
  char keypressed = NO_KEY; 
  myKeypad.getKey(); //If key is pressed, this key is stored in 'keypressed' variable; If key is not pressed, 'keypressed' variable will contain 'NO_KEY'.  
  if (keypressed != NO_KEY)
  {
    tone(13,10150);
    delay(100);
    noTone(13);
    Serial.print("Key pressed: ");
    Serial.println(keypressed);
    if (keypressed == '*')
    {
      Serial.println("pin code entering initiated");
      do
      {
        keypressed = myKeypad.getKey();
      }
      while (keypressed == NO_KEY);    
      Serial.print("Key pressed: ");
      Serial.println(keypressed);
      if (keypressed == '1')
      {
        Serial.print("alarm digit 1 entered: ");
        Serial.println(keypressed);   //consider replacing serial.print with Debug.Print(String string)
        do
        {
          keypressed = myKeypad.getKey();
        }
        while (keypressed == NO_KEY);
        Serial.print("Key pressed: ");
        Serial.println(keypressed);
        if (keypressed == '2')
        {
          Serial.print("alarm digit 2 entered: ");
          Serial.println(keypressed);   //consider replacing serial.print with Debug.Print(String string)
          do
          {
            keypressed = myKeypad.getKey();
          }
          while (keypressed == NO_KEY);
          Serial.print("Key pressed: ");
          Serial.println(keypressed);
          if (keypressed == '3')
          {
            Serial.print("alarm digit 3 entered: ");
            Serial.println(keypressed);   //consider replacing serial.print with Debug.Print(String string)
            do
            {
              keypressed = myKeypad.getKey();
            }
            while (keypressed == NO_KEY);
            Serial.print("Key pressed: ");
            Serial.println(keypressed);
            if (keypressed == '4')
            {
              Serial.print("alarm digit 4 entered: ");
              Serial.println(keypressed);   //consider replacing serial.print with Debug.Print(String string)
              do
              {
                keypressed = myKeypad.getKey();
              }
              while (keypressed == NO_KEY);
              Serial.print("Key pressed: ");
              Serial.println(keypressed);
              if (keypressed == '*')
              {
                Serial.print("pin code entering terminated: armed=");
                Serial.println(getIsArmed());
                tone(13,9150);
                Lcd.clear();
                Lcd.print("Alarm");
                Lcd.setCursor(0,1);
                Lcd.print("armed");
                lockDoor(MAIN_DOOR);
                delay(3500);
                noTone(13);
                Lcd.clear();
                Lcd.home();
                Lcd.print(getUserName1());
                Lcd.setCursor(0,1);
                Lcd.print(getUserName2());
              }
            }
          }
        }
      }
    } 
  }  
  delay(100);
}

String HomeSystem::homeSecurity::getUserName1()
{
  return m_userName.substring(1,16);
}

String HomeSystem::homeSecurity::getUserName2()
{
  return m_userName.substring(17,32);
}

void HomeSystem::homeSecurity::lockDoor(int door)
{
  Lock.write(0);
  //digitalWrite(door, LOW); //deactivate solenoid
}

void HomeSystem::homeSecurity::unlockDoor(int door)
{
  Lock.write(90);
  //digitalWrite(door, HIGH); //activate solenoid
}

bool HomeSystem::homeSecurity::getIsArmed()
{
  return m_isArmed;
}

HomeSystem::homeLight::homeLight()
{
  
}

void HomeSystem::homeLight::initialize()
{ 
  pinMode(PIR_SENSOR, INPUT);
//  pinMode(TABLE_LAMP, OUTPUT);
//  digitalWrite(TABLE_LAMP, LOW); //activate relay; turn normally closed light off
  pinMode(CEILING_LAMP, OUTPUT);
  digitalWrite(CEILING_LAMP, HIGH); //deactivate relay; turn normally open light off
  Serial.println("homeLight Initialized");
}

void HomeSystem::homeLight::process()
{
  if (digitalRead(PIR_SENSOR) == LOW)
  {
    if (command == "on")
      switchOn(CEILING_LAMP);
  }
  else
  {
    switchOff(CEILING_LAMP);
  }
  delay(100);
}

void HomeSystem::homeLight::switchOn(int light)
{
  digitalWrite(CEILING_LAMP, LOW); //activate relay; turn normally open light on
}

void HomeSystem::homeLight::switchOff(int light)
{
  digitalWrite(CEILING_LAMP, HIGH); //deactivate relay; turn normally open light off
}

HomeSystem::homeRemote::homeRemote()
{
  
}

void HomeSystem::homeRemote::initialize()
{
  Bluetooth.begin(9600); //set baud rate
  Serial.println("homeRemote Initialized");
}

void HomeSystem::homeRemote::process()
{
  command=""; //clear the data
  while(Bluetooth.available())
  {//while there is data available on the serial monitor
    command+=char(Bluetooth.read());//store string from serial command
    delay(1);
  }
  if(!Bluetooth.available())
  {
    if(command!="")
    {//if data is available
      Serial.print("homeRemote command received: ");
      Serial.println(command); //show the data
      Bluetooth.println("");
      //Bluetooth.println("homeRemote command sent.");
      if (command == "on")
      {
        digitalWrite(CEILING_LAMP, LOW); //activate relay; turn normally open light on
        Bluetooth.println("Ceiling Lamp turned on.");
      }
      else
      {
        digitalWrite(CEILING_LAMP, HIGH); //deactivate relay; turn normally open light off
        Bluetooth.println("Ceiling Lamp turned off.");
      }
    }
  }
}

int HomeSystem::homeRemote::executeCommand(String command)
{
  
}

void HomeSystem::homeRemote::sendFeedback(String feedbackMessage)
{
  
}

