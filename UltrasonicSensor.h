#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

class UltrasonicSensor {
private:
    int trigPin;
    int echoPin;

public:
    UltrasonicSensor(int trig, int echo);
    void begin();
    long readDistance();
};

#endif