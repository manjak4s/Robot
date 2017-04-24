#ifndef Motor_h
#define Motor_h

class Motor {
public:
    Motor(int speedPin, int forwardPin, int backwardPin);
    void stop();
    void setForwardSpeed(int sp);
    int getForwardSpeed();
    
    void setBackwardSpeed(int sp);
    int getBackwardSpeed();

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
