#include <Servo.h> // Include the Servo library

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

class UltrasonicSensor {
private:
    int trigPin;
    int echoPin;

public:
    UltrasonicSensor(int trig, int echo) : trigPin(trig), echoPin(echo) {}

    void begin() {
        pinMode(trigPin, OUTPUT);
        digitalWrite(trigPin, LOW);
        pinMode(echoPin, INPUT);
    }

    long readDistance() {
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
};

class ServoController {
private:
    Servo servo;
    int pin;

public:
    ServoController(int servoPin) : pin(servoPin) {}

    void begin() {
        servo.attach(pin);
    }

    void setPosition(int pos) {
        servo.write(pos);
        delay(15); // Wait for servo to reach position
    }
};

UltrasonicSensor sensor(7, 6); // Trig pin 7, Echo pin 6
ServoController servo(9);      // Servo on pin 9

void setup() {
    // Initialize serial communication at 9600 bits per second
    Serial.begin(9600);
    Serial.println("--- Arduino Booted ---");

    // Initialize sensor and servo
    sensor.begin();
    servo.begin();
}

void loop() {
    // Sweep from 0 degrees to 180 degrees
    for (int pos = 0; pos <= 180; pos += 1) {
        servo.setPosition(pos);
        long dist = sensor.readDistance();
        printToScreen(pos, dist);
    }

    // Sweep from 180 degrees to 0 degrees
    for (int pos = 180; pos >= 0; pos -= 1) {
        servo.setPosition(pos);
        long dist = sensor.readDistance();
        printToScreen(pos, dist);
    }
}

void printToScreen(int pos, long distanceCm) {
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


