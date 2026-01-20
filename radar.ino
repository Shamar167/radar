#include <Servo.h> // Include the Servo library

Servo myservo;     // Create a servo object to control the servo

// HC-SR04 pins
const int TRIG_PIN = 7;
const int ECHO_PIN = 6;

void setup() {
	// 1. Initialize serial communication at 9600 bits per second
	Serial.begin(9600);
	// 2. Print a simple string
	Serial.println("--- Arduino Booted ---");

	// SERVO
	myservo.attach(9); // Attach the servo on pin 9 to the servo object

	// SONAR
	pinMode(TRIG_PIN, OUTPUT);
	digitalWrite(TRIG_PIN, LOW);
	pinMode(ECHO_PIN, INPUT);
}

void loop()
{
	// Sweep from 0 degrees to 180 degrees
	for (int pos = 0; pos <= 180; pos += 1)
	{
		myservo.write(pos); // move servo
		delay(15);          // wait for servo
		long dist = readDistance();
		printToScreen(pos, dist);
	}

	// Sweep from 180 degrees to 0 degrees
	for (int pos = 180; pos >= 0; pos -= 1)
	{
		myservo.write(pos);
		delay(15);
		long dist = readDistance();
		printToScreen(pos, dist);
	}
}

// Triggers the HC-SR04 and returns distance in centimeters or -1 if out of range
long readDistance()
{
	// Ensure trigger is low
	digitalWrite(TRIG_PIN, LOW);
	delayMicroseconds(2);
	// Send 10us pulse to trigger
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN, LOW);

	// Read echo (timeout 30000 us ~ 5 meters). Returns duration in microseconds.
	unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
	if (duration == 0) {
		return -1; // out of range or no echo
		}

	// Convert to centimeters: speed of sound ~340 m/s => 29 microseconds per cm round-trip
	long distanceCm = (long)(duration / 29UL / 2UL);
	return distanceCm;
}

void printToScreen(int pos, long distanceCm)
{
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



