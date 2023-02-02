#include <Stepper.h>

const int stepsPerRevolution = 32;
Stepper myStepper(stepsPerRevolution, 6, 9, 10, 11);

void setup() {
    Serial.begin(9600);

}

void loop() {

    myStepper.setSpeed(700);
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution*64);
    delay(100);

    // step one revolution in the other direction:
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution*64);
    delay(100);
}
