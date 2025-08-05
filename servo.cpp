#include <Servo.h>

// --- Pin Definitions ---
const int SERVO_CONTROL_PIN = 9;   // The PWM pin connected to the servo's signal wire.
const int SERVO_FEEDBACK_PIN = A0; // The Analog pin connected to the new feedback wire.

// Create a servo object
Servo myServo;

// --- Calibration ---
// These are the raw analog values your specific servo outputs at 0 and 180 degrees.
// You MUST find these values for your servo for the reading to be accurate!
// To calibrate: Upload the code, open the Serial Monitor, and move the servo to 0 and 180.
// Note the minimum and maximum values you see and put them here.
const int MIN_ANALOG_VALUE = 0;    // Example: Raw analog value at 0 degrees
const int MAX_ANALOG_VALUE = 1023; // Example: Raw analog value at 180 degrees

void setup()
{
    // Start serial communication to display the results
    Serial.begin(9600);

    // Attach the servo to its control pin
    myServo.attach(SERVO_CONTROL_PIN);

    Serial.println("Servo Feedback Test Initialized.");
    Serial.println("---------------------------------");
}

void loop()
{
    // --- Sweep from 0 to 180 degrees ---
    for (int targetAngle = 0; targetAngle <= 180; targetAngle++)
    {
        // Command the servo to move to the target angle
        myServo.write(targetAngle);

        // Wait a moment for the servo to start moving
        delay(20);

        // Read the actual position from the feedback wire
        int analogValue = analogRead(SERVO_FEEDBACK_PIN);

        // Map the raw analog value to an angle (0-180) using your calibration values
        int actualAngle = map(analogValue, MIN_ANALOG_VALUE, MAX_ANALOG_VALUE, 0, 180);

        // Print the results to the Serial Monitor
        Serial.print("Target: ");
        Serial.print(targetAngle);
        Serial.print(" deg | Actual: ");
        Serial.print(actualAngle);
        Serial.println(" deg");
    }

    delay(500); // Pause at the end

    // --- Sweep from 180 back to 0 degrees ---
    for (int targetAngle = 180; targetAngle >= 0; targetAngle--)
    {
        myServo.write(targetAngle);
        delay(20);

        int analogValue = analogRead(SERVO_FEEDBACK_PIN);
        int actualAngle = map(analogValue, MIN_ANALOG_VALUE, MAX_ANALOG_VALUE, 0, 180);

        Serial.print("Target: ");
        Serial.print(targetAngle);
        Serial.print(" deg | Actual: ");
        Serial.print(actualAngle);
        Serial.println(" deg");
    }

    delay(500); // Pause at the end
}