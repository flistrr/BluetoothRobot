#include <Arduino.h>
#include <AFMotor_R4.h>
#include "Sound.h"

class Robot
{
private:
    AF_DCMotor motorFrontRight;
    AF_DCMotor motorFrontLeft;
    AF_DCMotor motorBackLeft;
    AF_DCMotor motorBackRight;

    Sound audio;

    int pinHeadLed;
    int pinBackLed;
    int pinFrontSensor;
    int pinBackSensor;

    int currentSpeed;

public:
    const int firstGear = 65;
    const int secondGear = 130;
    const int thirdGear = 195;
    const int fourthGear = 255;

    Robot() : motorFrontRight(1), motorFrontLeft(2), motorBackLeft(3), motorBackRight(4)
    {
        currentSpeed = 255;
    }

    void begin(int buzzer, int headLed, int backLed, int frontSensor, int backSensor)
    {
        pinHeadLed = headLed;
        pinBackLed = backLed;
        pinFrontSensor = frontSensor;
        pinBackSensor = backSensor;

        audio.begin(buzzer);

        pinMode(pinHeadLed, OUTPUT);
        pinMode(pinBackLed, OUTPUT);
        pinMode(pinFrontSensor, INPUT);
        pinMode(pinBackSensor, INPUT);

        audio.playStartup();

        stop();
    }

    void setSpeed(int targetSpeed)
    {
        currentSpeed = targetSpeed;
        updateMotorSpeed(targetSpeed, targetSpeed, targetSpeed, targetSpeed);
    }

    void updateMotorSpeed(int frontLeft, int frontRight, int backLeft, int backRight)
    {
        motorFrontLeft.setSpeed(frontLeft);
        motorFrontRight.setSpeed(frontRight);
        motorBackLeft.setSpeed(backLeft);
        motorBackRight.setSpeed(backRight);
    }

    bool checkObstacle()
    {
        if (digitalRead(pinFrontSensor) == LOW || digitalRead(pinBackSensor) == LOW)
        {
            return true;
        }
        return false;
    }

    void runMotors(uint8_t dir)
    {
        motorFrontLeft.run(dir);
        motorFrontRight.run(dir);
        motorBackLeft.run(dir);
        motorBackRight.run(dir);
    }

    void checkIfDirectionIsBlocked()
    {
        if (checkObstacle())
        {
            stop();
            audio.buzz();
            return;
        }
    }

    void forward()
    {
        checkIfDirectionIsBlocked();
        updateMotorSpeed(currentSpeed, currentSpeed, currentSpeed, currentSpeed);
        runMotors(FORWARD);
    }

    void back()
    {
        checkIfDirectionIsBlocked();
        digitalWrite(pinBackLed, HIGH);
        updateMotorSpeed(currentSpeed, currentSpeed, currentSpeed, currentSpeed);
        runMotors(BACKWARD);
    }

    void left()
    {
        updateMotorSpeed(currentSpeed, currentSpeed, currentSpeed, currentSpeed);
        motorFrontLeft.run(BACKWARD);
        motorBackLeft.run(BACKWARD);
        motorFrontRight.run(FORWARD);
        motorBackRight.run(FORWARD);
    }

    void right()
    {
        updateMotorSpeed(currentSpeed, currentSpeed, currentSpeed, currentSpeed);
        motorFrontLeft.run(FORWARD);
        motorBackLeft.run(FORWARD);
        motorFrontRight.run(BACKWARD);
        motorBackRight.run(BACKWARD);
    }

    void forwardLeft()
    {
        checkIfDirectionIsBlocked();
        int slow = currentSpeed / 4;
        updateMotorSpeed(slow, currentSpeed, slow, currentSpeed);
        runMotors(FORWARD);
    }

    void forwardRight()
    {
        checkIfDirectionIsBlocked();
        int slow = currentSpeed / 4;
        updateMotorSpeed(currentSpeed, slow, currentSpeed, slow);
        runMotors(FORWARD);
    }

    void backLeft()
    {
        checkIfDirectionIsBlocked();
        digitalWrite(pinBackLed, HIGH);
        int slow = currentSpeed / 4;
        updateMotorSpeed(slow, currentSpeed, slow, currentSpeed);
        runMotors(BACKWARD);
    }

    void backRight()
    {
        checkIfDirectionIsBlocked();
        digitalWrite(pinBackLed, HIGH);
        int slow = currentSpeed / 4;
        updateMotorSpeed(currentSpeed, slow, currentSpeed, slow);
        runMotors(BACKWARD);
    }

    void stop()
    {
        digitalWrite(pinBackLed, LOW);
        motorFrontLeft.run(RELEASE);
        motorFrontRight.run(RELEASE);
        motorBackLeft.run(RELEASE);
        motorBackRight.run(RELEASE);
    }

    void lightsOn()
    {
        digitalWrite(pinHeadLed, HIGH);
    }

    void lightsOff()
    {
        digitalWrite(pinHeadLed, LOW);
    }

    void buzz()
    {
        audio.buzz();
    }
};