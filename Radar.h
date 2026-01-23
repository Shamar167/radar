#ifndef RADAR_H
#define RADAR_H

#include "UltrasonicSensor.h"
#include "ServoController.h"

class Radar {
private:
    UltrasonicSensor& sensor;
    ServoController& servo;
    int stepSize;

public:
    Radar(UltrasonicSensor& sens, ServoController& serv, int step = 1);
    void begin();
    void sweepAndScan();

private:
    void printScanData(int pos, long distanceCm);
};

#endif