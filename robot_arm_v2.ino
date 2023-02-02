#include <Stepper.h>

const int stepsPerRevolution = 64;
Stepper myStepper(stepsPerRevolution, 6, 9, 10, 11);

void setup() {
    myStepper.setSpeed(30);
    Serial.begin(9600);

}

void loop() {

    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
    delay(100);

    // step one revolution in the other direction:
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution);
    delay(100);
}
