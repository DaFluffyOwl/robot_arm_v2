#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 6, 10, 9, 11);
void setup() {
    Serial.begin(9600);
    myStepper.setSpeed(12);

}

void loop() {

    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
    delay(200);

    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution);
    delay(200);
}
