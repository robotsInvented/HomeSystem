/*
  HomeSystem.cpp - Library for flashing Morse code.
  Created by RobotsInvented, March 17, 2016.
  Released into the public domain.
*/

#include "Arduino.h"
#include "HomeSystem.h"

//Pot for LCD contrast:
//Voltage Vcc to V0 - 4.15V
//Voltage V0 to Gnd - 0.92V

LiquidCrystal Lcd(7,8,9,10,11,12);

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

String message; //string that stores the incoming message

Servo myservo;

HomeSystem::HomeSystem(char* userName1,char* userName2)
{
  homeSecurity.m_userName1 = userName1;
  homeSecurity.m_userName2 = userName2;
}

void HomeSystem::initialize()
{
  homeSecurity.initialize();
  Serial.begin(250000); //set baud rate
  myservo.attach(6);
  pinMode(4, INPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH); //deactivate relay
  //Lcd.print(userName);
  //Delay(3000);
  //blink led
  //play buzzer
}

HomeSystem::homeSecurity::homeSecurity()
{
  
}

void HomeSystem::homeSecurity::initialize()
{
  Lcd.begin(16,2);
  tone(13,90);
  delay(95);
  noTone(13);
  delay(5);
  tone(13,15150);
  delay(100);
  noTone(13);
  Lcd.home();
  Lcd.print("homeSecurity");
  delay(750);
  Lcd.clear();
  Lcd.print("homeSecurity.rob");
  Serial.println("homeSecurity.rob");
  Lcd.setCursor(0,1);
  Lcd.print("otsInvented");
  delay(750);
  Lcd.clear();
  Lcd.print("homeSecurity.rob");
  Lcd.setCursor(0,1);
  Lcd.print("otsInvented.asia");
  delay(3500);
  Lcd.clear();
  Lcd.home();
  Lcd.print(getUserName1());
  Lcd.setCursor(0,1);
  Lcd.print(getUserName2());
  //Lcd.clear();
  unlockDoor(MAIN_DOOR);
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

char* HomeSystem::homeSecurity::getUserName1()
{
  return m_userName1;
}

char* HomeSystem::homeSecurity::getUserName2()
{
  return m_userName2;
}

void HomeSystem::homeSecurity::lockDoor(int door)
{
  myservo.write(90); //lock
}

void HomeSystem::homeSecurity::unlockDoor(int door)
{
  myservo.write(0); //unlock
}

bool HomeSystem::homeSecurity::getIsArmed()
{
  return m_isArmed;
}

HomeSystem::homeLight::homeLight()
{
  
}

void HomeSystem::homeLight::process()
{
  if (digitalRead(5) == LOW)
  {
  digitalWrite(4, HIGH); //deactivate relay
  }
  else
  {
  digitalWrite(4, LOW); //activate relay  
  }
  delay(100);
}

void HomeSystem::homeLight::switchOn(int light)
{
  
}

void HomeSystem::homeLight::switchOff(int light)
{
  
}

