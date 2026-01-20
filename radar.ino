#include <Servo.h> // Include the Servo library

Servo myservo;     // Create a servo object to control the servo

void setup() {
	// 1. Initialize serial communication at 9600 bits per second
  	Serial.begin(9600); 
  
  	// 2. Print a simple string
  	Serial.println("--- Arduino Booted ---");

	//SERVO CODE
  	myservo.attach(9); // Attach the servo on pin 9 to the servo object

	//SONAR CODE
}

void loop() 
{

	//SERVO CODE

  	// Sweep from 0 degrees to 180 degrees
  	for (int pos = 0; pos <= 180; pos += 1) 
	{
    		myservo.write(pos); // Tell servo to go to position in variable 'pos'
    		delay(15);          // Waits 15ms for the servo to reach the position
		printToScreen(pos);
  	}

  	// Sweep from 180 degrees to 0 degrees
  	for (int pos = 180; pos >= 0; pos -= 1) 
	{
    		myservo.write(pos); // Tell servo to go to position in variable 'pos'
    		delay(15);          // Waits 15ms for the servo to reach the position
		printToScreen(pos);
  	}
}

void printToScreen(int pos)
{
	//SONAR CODE
  	Serial.println("LOOP");
	Serial.print("position in degrees: ");
  	Serial.print(pos);

}



