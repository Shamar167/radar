#include "ServoController.h"
#include <Arduino.h>

ServoController::ServoController(int servoPin) : pin(servoPin) {}

void ServoController::begin() {
    servo.attach(pin);
}

void ServoController::setPosition(int pos) {
    servo.write(pos);
    delay(15); // Wait for servo to reach position
}