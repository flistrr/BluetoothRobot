#include "Robot.h"

Robot bluetoothRobot;

const int PIN_BUZZER = 2;
const int PIN_HEAD_LED = A5;
const int PIN_BACK_LED = A4;
const int PIN_FRONT_SENSOR = A1; 
const int PIN_BACK_SENSOR = A2; 

void setup() {
  Serial.begin(9600);
  bluetoothRobot.begin(PIN_BUZZER, PIN_HEAD_LED, PIN_BACK_LED, PIN_FRONT_SENSOR, PIN_BACK_SENSOR);
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    switch (cmd) {
      case 'F': bluetoothRobot.forward(); break;
      case 'B': bluetoothRobot.back(); break;
      case 'L': bluetoothRobot.left(); break;
      case 'R': bluetoothRobot.right(); break;
      
      case 'G': bluetoothRobot.forwardLeft(); break;
      case 'H': bluetoothRobot.forwardRight(); break;
      case 'I': bluetoothRobot.backLeft(); break;
      case 'J': bluetoothRobot.backRight(); break;
      
      case 'S': bluetoothRobot.stop(); break;
      case 'Y': bluetoothRobot.buzz(); break;
      case 'U': bluetoothRobot.lightsOn(); break;
      case 'u': bluetoothRobot.lightsOff(); break;
      
      case '1': bluetoothRobot.setSpeed(bluetoothRobot.firstGear); break;
      case '2': bluetoothRobot.setSpeed(bluetoothRobot.secondGear); break;
      case '3': bluetoothRobot.setSpeed(bluetoothRobot.thirdGear); break;
      case '4': bluetoothRobot.setSpeed(bluetoothRobot.fourthGear); break;
    }
  }
}