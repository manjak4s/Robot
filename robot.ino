#include <SoftwareSerial.h>
#include "Motor.h"

//Software Rx Tx for receiving commands
SoftwareSerial softSerial(2, 4);

char const* commands[] = { "f", "b", "l", "r", "s" };
enum { FORWARD, BACKWARD, LEFT, RIGHT, STOP };

enum MotorPin { 
    FL_MOTOR = 11, //front left
    FR_MOTOR = 6, //front right
    RL_MOTOR = 9, //rear left
    RR_MOTOR = 10 //rear right
};

enum DirectionPin { 
    LEFT_FWD = 8, 
    LEFT_BWD = 7, 
    RIGHT_FWD = 13, 
    RIGHT_BWD = 12 
};

//Default MOTORs' speed values
enum DefaultSpeed {
    FL_MOTOR_FWD_SPEED = 218,
    FL_MOTOR_BWD_SPEED = 164,
    FR_MOTOR_FWD_SPEED = 228,
    FR_MOTOR_BWD_SPEED = 170,
    RL_MOTOR_FWD_SPEED = 255,
    RL_MOTOR_BWD_SPEED = 255,
    RR_MOTOR_FWD_SPEED = 185,
    RR_MOTOR_BWD_SPEED = 135
};

Motor flMotor(FL_MOTOR, LEFT_FWD, LEFT_BWD);
Motor frMotor(FR_MOTOR, RIGHT_FWD, RIGHT_BWD);
Motor rlMotor(RL_MOTOR, LEFT_FWD, LEFT_BWD);
Motor rrMotor(RR_MOTOR, RIGHT_FWD, RIGHT_BWD);

//This lets you run the loop a single time for testing
boolean run = true;

void setup() 
{
    Serial.begin(115200);
    softSerial.begin(115200);

    flMotor.setForwardSpeed(FL_MOTOR_FWD_SPEED);
    flMotor.setBackwardSpeed(FL_MOTOR_BWD_SPEED);

    frMotor.setForwardSpeed(FR_MOTOR_FWD_SPEED);
    frMotor.setBackwardSpeed(FR_MOTOR_BWD_SPEED);

    rlMotor.setForwardSpeed(RL_MOTOR_FWD_SPEED);
    rlMotor.setBackwardSpeed(RL_MOTOR_BWD_SPEED);

    rrMotor.setForwardSpeed(RR_MOTOR_FWD_SPEED);
    rrMotor.setBackwardSpeed(RR_MOTOR_BWD_SPEED);
}

void stop() 
{
    flMotor.stop();
    frMotor.stop();
    rlMotor.stop();
    rrMotor.stop();
}

void moveForward() 
{
    flMotor.moveForward();
    frMotor.moveForward();
    rlMotor.moveForward();
    rrMotor.moveForward();
}

void moveBackward()
{
    flMotor.moveBackward();
    frMotor.moveBackward();
    rlMotor.moveBackward();
    rrMotor.moveBackward();
}

void turnLeft() 
{
    flMotor.moveBackward();
    frMotor.moveForward();
    rlMotor.moveBackward();
    rrMotor.moveForward();
}

void turnRight() 
{
    flMotor.moveForward();
    frMotor.moveBackward();
    rlMotor.moveForward();
    rrMotor.moveBackward();
}

void handleCommand(String command) {
   if(command == commands[FORWARD]) {
       Serial.println("forward");
       moveForward();
    }
    else if(command == commands[BACKWARD]) {
       Serial.println("backward");
       moveBackward();
    }
    else if(command == commands[LEFT]) {
       Serial.println("left");
       turnLeft();
    }
    else if(command == commands[RIGHT]) {
       Serial.println("right");
       turnRight();
    }
    else {
       Serial.println("break");
       stop();
    }
}

void loop() 
{
    if(softSerial.available() > 0) 
    {
        String msg = softSerial.readStringUntil('\n');
        Serial.print("received message: ");
        Serial.println(msg);
        handleCommand(msg);
    }
}
