#include <SoftwareSerial.h>

//Software Rx Tx for receiving commands
SoftwareSerial softSerial(2, 3);

char const* commands[] = { "f", "b", "l", "r", "s" };
enum { FORWARD, BACKWARD, LEFT, RIGHT, STOP };

int commandDuration = 0;

// Motor A pins (enableA = enable motor, pinA1 = forward, pinA2 = backward)
int enableA = 11;
int pinA1 = 12;
int pinA2 = 13;

//Motor B pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int enableB = 10;
int pinB1 = 9;
int pinB2 = 8;

//Motor C pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
//int enableC = 5;
int pinC1 = 6;
int pinC2 = 5;

//Motor D pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
//int enableD = 6;
int pinD1 = 4;
int pinD2 = 7;

//This lets you run the loop a single time for testing
boolean run = true;

void setup() {
  Serial.begin(115200);
  softSerial.begin(115200);
  
 pinMode(enableA, OUTPUT);
 pinMode(pinA1, OUTPUT);
 pinMode(pinA2, OUTPUT);
 
 pinMode(enableB, OUTPUT);
 pinMode(pinB1, OUTPUT);
 pinMode(pinB2, OUTPUT);
 
// pinMode(enableC, OUTPUT);
 pinMode(pinC1, OUTPUT);
 pinMode(pinC2, OUTPUT);
 
 //pinMode(enableD, OUTPUT);
 pinMode(pinD1, OUTPUT);
 pinMode(pinD2, OUTPUT);
}
void loop() {
  enableMotors();
  if(softSerial.available() > 0) {
     String msg = softSerial.readStringUntil('\n');
     Serial.print("received message: ");
     Serial.println(msg);
     handleCommand(msg);
  }
}

void handleCommand(String command) {
    if(command == commands[FORWARD]) {
        Serial.println("forward");
        forward(commandDuration);
     }
     else if(command == commands[BACKWARD]) {
        Serial.println("backward");
        backward(commandDuration);
     }
     else if(command == commands[LEFT]) {
        Serial.println("left");
        turnLeft(commandDuration);
     }
     else if(command == commands[RIGHT]) {
        Serial.println("right");
        turnRight(commandDuration);
     }
     else {
        Serial.println("break");
        coast(0);
     }
}

//Define high-level H-bridge commands
 
void enableMotors()
{
 motorAOn();
 motorBOn();
}
 
void disableMotors()
{
 motorAOff();
 motorBOff();
}
 
void forward(int time)
{
 motorAForward();
 motorBForward();
 delay(time);
}
 
void backward(int time)
{
 motorABackward();
 motorBBackward();
 delay(time);
}
 
void turnLeft(int time)
{
 motorABackward();
 motorBForward();
 delay(time);
}
 
void turnRight(int time)
{
 motorAForward();
 motorBBackward();
 delay(time);
}
 
void coast(int time)
{
 motorACoast();
 motorBCoast();
 delay(time);
}
 
void brake(int time)
{
 motorABrake();
 motorBBrake();
 delay(time);
}
//Define low-level H-bridge commands
 
//enable motors
void motorAOn()
{
 digitalWrite(enableA, HIGH);
}
 
void motorBOn()
{
 digitalWrite(enableB, HIGH);
}
 
 //disable motors
void motorAOff()
{
 digitalWrite(enableB, LOW);
}
 
void motorBOff()
{
 digitalWrite(enableA, LOW);
}
 
 //motor A controls
void motorAForward()
{
 digitalWrite(pinA1, HIGH);
 digitalWrite(pinA2, LOW);
}
 
void motorABackward()
{
 digitalWrite(pinA1, LOW);
 digitalWrite(pinA2, HIGH);
}
 
//motor B controls
void motorBForward()
{
 digitalWrite(pinB1, HIGH);
 digitalWrite(pinB2, LOW);
}
 
void motorBBackward()
{
 digitalWrite(pinB1, LOW);
 digitalWrite(pinB2, HIGH);
}
 
//coasting and braking
void motorACoast()
{
 digitalWrite(pinA1, LOW);
 digitalWrite(pinA2, LOW);
}
 
void motorABrake()
{
 digitalWrite(pinA1, HIGH);
 digitalWrite(pinA2, HIGH);
}
 
void motorBCoast()
{
 digitalWrite(pinB1, LOW);
 digitalWrite(pinB2, LOW);
}
 
void motorBBrake()
{
 digitalWrite(pinB1, HIGH);
 digitalWrite(pinB2, HIGH);
}
