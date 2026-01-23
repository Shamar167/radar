#include <Servo.h> // Include the Servo library
#include "UltrasonicSensor.h"
#include "ServoController.h"
#include "Radar.h"

/*
Wiring Instructions for Breadboard:

- Connect Arduino GND to the breadboard's ground rail (blue or black line).
- Connect Arduino 5V to the breadboard's power rail (red line).

Servo Motor (e.g., SG90 or similar):
- Signal wire (usually yellow or orange) -> Arduino pin 9
- Power wire (red) -> Breadboard power rail (+5V)
- Ground wire (black or brown) -> Breadboard ground rail (GND)

Ultrasonic Sensor (HC-SR04):
- VCC -> Breadboard power rail (+5V)
- GND -> Breadboard ground rail (GND)
- Trig -> Arduino pin 7
- Echo -> Arduino pin 6

Ensure the servo and sensor share the same ground and power rails on the breadboard.
*/

UltrasonicSensor sensor(7, 6); // Trig pin 7, Echo pin 6
ServoController servo(9);      // Servo on pin 9
Radar radar(sensor, servo);    // Radar system

void setup() {
    // Initialize serial communication at 9600 bits per second
    Serial.begin(9600);
    Serial.println("--- Arduino Booted ---");

    // Initialize radar system
    radar.begin();
}

void loop() {
    radar.sweepAndScan();
}

