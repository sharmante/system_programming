#include <wiringPi.h>
#include <stdio.h>

// Define GPIO pins for IR sensors
#define LEFT_SENSOR_PIN 0  // GPIO 17 (WiringPi pin 0)
#define RIGHT_SENSOR_PIN 1 // GPIO 18 (WiringPi pin 1)

// Define motor control pins
#define LEFT_MOTOR_FORWARD_PIN 2  // GPIO 27 (WiringPi pin 2)
#define LEFT_MOTOR_BACKWARD_PIN 3 // GPIO 22 (WiringPi pin 3)
#define RIGHT_MOTOR_FORWARD_PIN 4 // GPIO 23 (WiringPi pin 4)
#define RIGHT_MOTOR_BACKWARD_PIN 5 // GPIO 24 (WiringPi pin 5)

// Function prototypes
void setup();
void loop();
void stopMotors();
void moveForward();
void turnLeft();
void turnRight();

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("Setup wiringPi failed!");
        return 1;
    }

    setup();

    while (1) {
        loop();
    }

    return 0;
}

void setup() {
    // Set up IR sensor pins as input
    pinMode(LEFT_SENSOR_PIN, INPUT);
    pinMode(RIGHT_SENSOR_PIN, INPUT);

    // Set up motor control pins as output
    pinMode(LEFT_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD_PIN, OUTPUT);
}

void loop() {
    int leftSensorValue = digitalRead(LEFT_SENSOR_PIN);
    int rightSensorValue = digitalRead(RIGHT_SENSOR_PIN);

    if (leftSensorValue == LOW && rightSensorValue == LOW) {
        moveForward();
    } else if (leftSensorValue == LOW && rightSensorValue == HIGH) {
        turnRight();
    } else if (leftSensorValue == HIGH && rightSensorValue == LOW) {
        turnLeft();
    } else {
        stopMotors();
    }

    delay(100); // Delay for stability
}

void stopMotors() {
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
}

void moveForward() {
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
}

void turnLeft() {
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
}

void turnRight() {
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, HIGH);
}
