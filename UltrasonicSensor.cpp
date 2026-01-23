#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(int trig, int echo) : trigPin(trig), echoPin(echo) {}

void UltrasonicSensor::begin() {
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
}

long UltrasonicSensor::readDistance() {
    // Ensure trigger is low
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Send 10us pulse to trigger
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read echo (timeout 30000 us ~ 5 meters). Returns duration in microseconds.
    unsigned long duration = pulseIn(echoPin, HIGH, 30000UL);
    if (duration == 0) {
        return -1; // out of range or no echo
    }

    // Convert to centimeters: speed of sound ~340 m/s => 29 microseconds per cm round-trip
    long distanceCm = (long)(duration / 29UL / 2UL);
    return distanceCm;
}