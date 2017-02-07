// Motor A pins (enableA = enable motor, pinA1 = forward, pinA2 = backward)
int enableA = 11;
int pinA1 = 12;
int pinA2 = 13;

//Motor B pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int enableB = 10;
int pinB1 = 9;
int pinB2 = 8;

//Motor C pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int enableC = 5;
int pinC1 = 4;
int pinC2 = 3;

//Motor D pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int enableD = 6;
int pinD1 = 2;
int pinD2 = 7;

//This lets you run the loop a single time for testing
boolean run = true;

void setup() {
 pinMode(enableA, OUTPUT);
 pinMode(pinA1, OUTPUT);
 pinMode(pinA2, OUTPUT);
 
 pinMode(enableB, OUTPUT);
 pinMode(pinB1, OUTPUT);
 pinMode(pinB2, OUTPUT);
 
 pinMode(enableC, OUTPUT);
 pinMode(pinC1, OUTPUT);
 pinMode(pinC2, OUTPUT);
 
 pinMode(enableD, OUTPUT);
 pinMode(pinD1, OUTPUT);
 pinMode(pinD2, OUTPUT);
}
void loop() {
  // эта функция обеспечит вращение двигателей в двух направлениях на установленной скорости

// запуск двигателя A

digitalWrite(pinA1, HIGH);

digitalWrite(pinA2, LOW);

// устанавливаем скорость 200 из доступного диапазона 0~255

analogWrite(enableA, 255);

// запуск двигателя B

digitalWrite(pinB1, HIGH);

digitalWrite(pinB2, LOW);

// устанавливаем скорость 200 из доступного диапазона 0~255

analogWrite(enableB, 255);

// запуск двигателя C

digitalWrite(pinC1, LOW);

digitalWrite(pinC2, HIGH);

// устанавливаем скорость 200 из доступного диапазона 0~255

analogWrite(enableC, 255);


// запуск двигателя D

digitalWrite(pinD1, HIGH);

digitalWrite(pinD2, LOW);

// устанавливаем скорость 200 из доступного диапазона 0~255

analogWrite(enableD, 255);


delay(2000);

// меняем направление вращения двигателей

digitalWrite(pinA1, LOW);

digitalWrite(pinA2, HIGH);

digitalWrite(pinB1, LOW);

digitalWrite(pinB2, HIGH);

digitalWrite(pinC1, HIGH);

digitalWrite(pinC2, LOW);

digitalWrite(pinD1, LOW);

digitalWrite(pinD2, HIGH);

delay(2000);

// выключаем двигатели

digitalWrite(pinA1, LOW);

digitalWrite(pinA2, LOW);

digitalWrite(pinB1, LOW);

digitalWrite(pinB2, LOW);

digitalWrite(pinC1, LOW);

digitalWrite(pinC2, LOW);

digitalWrite(pinD1, LOW);

digitalWrite(pinD2, LOW);

delay(2000);
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
