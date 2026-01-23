#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Servo.h>

class ServoController {
private:
    Servo servo;
    int pin;

public:
    ServoController(int servoPin);
    void begin();
    void setPosition(int pos);
};

#endif