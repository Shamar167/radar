#include "Radar.h"
#include <Arduino.h>

Radar::Radar(UltrasonicSensor& sens, ServoController& serv, int step) : sensor(sens), servo(serv), stepSize(step) {}

void Radar::begin() {
    sensor.begin();
    servo.begin();
}

void Radar::sweepAndScan() {
    // Sweep from 0 degrees to 180 degrees
    for (int pos = 0; pos <= 180; pos += stepSize) {
        servo.setPosition(pos);
        long dist = sensor.readDistance();
        printScanData(pos, dist);
    }

    // Sweep from 180 degrees to 0 degrees
    for (int pos = 180; pos >= 0; pos -= stepSize) {
        servo.setPosition(pos);
        long dist = sensor.readDistance();
        printScanData(pos, dist);
    }
}

void Radar::printScanData(int pos, long distanceCm) {
    Serial.println("LOOP");
    Serial.print("position in degrees: ");
    Serial.print(pos);
    Serial.print("  | distance: ");
    if (distanceCm < 0) {
        Serial.println("Out of range");
    } else {
        Serial.print(distanceCm);
        Serial.println(" cm");
    }
}