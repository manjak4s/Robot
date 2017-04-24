#include "Motor.h"

Motor::Motor(int speedPin, int forwardPin, int backwardPin)
{
    _speedPin = speedPin;
    _fwdPin = forwardPin;
    _bwdPin = backwardPin;

    pinMode(_speedPin, OUTPUT);
    pinMode(_fwdPin, OUTPUT);
    pinMode(_bwdPin, OUTPUT);
}

void Motor::stop()
{
	_currentSpeed = 0;
	updateSpeed();
	_state = STOPPED;
}
    
void Motor::setForwardSpeed(int sp)
{
	_fwdSpeed = sp;
	if(_state == MOVING_FORWARD)
	{
		_currentSpeed = _fwdSpeed;
		updateSpeed();
	}
}

int Motor::getForwardSpeed()
{
  return _fwdSpeed;
}

void Motor::setBackwardSpeed(int sp) 
{
	_bwdSpeed = sp;
	if(_state == MOVING_BACKWARD)
	{
		_currentSpeed = _state;
		updateSpeed();
	}
}

int Motor::getBackwardSpeed()
{
  return _bwdSpeed;
}

void Motor::moveForward()
{
	digitalWrite(_fwdPin, HIGH);
	digitalWrite(_bwdPin, LOW);
	_currentSpeed = _fwdSpeed;
	updateSpeed();
	_state = MOVING_FORWARD;
}

void Motor::moveBackward()
{
	digitalWrite(_fwdPin, LOW);
	digitalWrite(_bwdPin, HIGH);
	_currentSpeed = _bwdSpeed;
	updateSpeed();
	_state = MOVING_BACKWARD;
}

void Motor::updateSpeed()
{
	analogWrite(_speedPin, _currentSpeed);
}
