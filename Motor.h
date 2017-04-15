#ifndef Motor_h
#define Motor_h

class Motor {
public:
    Motor(int speedPin, int forwardPin, int backwardPin);
    void stop();
    void setForwardSpeed(int sp);
    void setBackwardSpeed(int sp);

    void moveForward();
    void moveBackward();
    

private:
    enum MotorState { STOPPED, MOVING_FORWARD, MOVING_BACKWARD };
    int _speedPin, _fwdPin, _bwdPin;
    int _fwdSpeed, _bwdSpeed, _currentSpeed;
    MotorState _state;
    void updateSpeed();
};

#endif
