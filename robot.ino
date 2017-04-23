#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "Motor.h"

//Software Rx Tx for receiving commands
SoftwareSerial softSerial(2, 4);

char const* commands[] = { "f", "b", "l", "r", "s", "gs", "ss:", "rs" };
enum { FORWARD, BACKWARD, LEFT, RIGHT, STOP, GET_SETTINGS, SET_SETTINGS, RESET_SETTINGS };

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

Motor flMotor(FL_MOTOR, LEFT_FWD, LEFT_BWD);
Motor frMotor(FR_MOTOR, RIGHT_FWD, RIGHT_BWD);
Motor rlMotor(RL_MOTOR, LEFT_FWD, LEFT_BWD);
Motor rrMotor(RR_MOTOR, RIGHT_FWD, RIGHT_BWD);

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

void getSettings()
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["fl_fwd"] = flMotor.getForwardSpeed();
    root["fl_bwd"] = flMotor.getBackwardSpeed();
    root["fr_fwd"] = frMotor.getForwardSpeed();
    root["fr_bwd"] = frMotor.getBackwardSpeed();
    root["rl_fwd"] = rlMotor.getForwardSpeed();
    root["rl_bwd"] = rlMotor.getBackwardSpeed();
    root["rr_fwd"] = rrMotor.getForwardSpeed();
    root["rr_bwd"] = rrMotor.getBackwardSpeed();
    root.printTo(softSerial);
}

void setSettings(String settingsJson)
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(settingsJson);

    if (!root.success()) 
    {
        softSerial.print("400\n");
        return;   
    }

    flMotor.setForwardSpeed(root["fl_fwd"]);
    flMotor.setBackwardSpeed(root["fl_bwd"]);
    frMotor.setForwardSpeed(root["fr_fwd"]);
    frMotor.setBackwardSpeed(root["fr_bwd"]);
    rlMotor.setForwardSpeed(root["rl_fwd"]);
    rlMotor.setBackwardSpeed(root["rl_bwd"]);
    rrMotor.setForwardSpeed(root["rr_fwd"]);
    rrMotor.setBackwardSpeed(root["rr_bwd"]);
    
    softSerial.print("200\n");
}

void resetSpeed()
{
    flMotor.setForwardSpeed(255);
    flMotor.setBackwardSpeed(255);

    frMotor.setForwardSpeed(255);
    frMotor.setBackwardSpeed(255);

    rlMotor.setForwardSpeed(255);
    rlMotor.setBackwardSpeed(255);

    rrMotor.setForwardSpeed(255);
    rrMotor.setBackwardSpeed(255);
}

void resetSettings()
{
    resetSpeed();
    softSerial.print("200\n");
}

void handleCommand(String command) 
{
   if(command == commands[FORWARD]) 
   {
        moveForward();
    }
    else if(command == commands[BACKWARD]) 
    {
        moveBackward();
    }
    else if(command == commands[LEFT]) 
    {
        turnLeft();
    }
    else if(command == commands[RIGHT]) 
    {
        turnRight();
    }
    else if(command == commands[GET_SETTINGS])
    {
        getSettings();       
    }
    else if(command.startsWith(commands[SET_SETTINGS]))
    {
        setSettings(command.substring(3));
    }
    else if(command == commands[RESET_SETTINGS])
    {
        resetSettings();
    }
    else
    {
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

void setup() 
{
    Serial.begin(9600);
    softSerial.begin(9600);

    resetSpeed();
}

