#include <Stepper.h>
#include <MPU6050_light.h>
#include <Wire.h>

MPU6050 gyro(Wire);

int gyro_pin = 4;

float* coord_ptr;

int Speed = 12;
int X, Y, Z;

const int stepsPerRevolution = 2048;
Stepper xStepper(stepsPerRevolution, 6, 10, 9, 11);




void setup() {

    xStepper.setSpeed(Speed);

    pinMode(gyro_pin, OUTPUT);
    digitalWrite(gyro_pin, LOW);

    gyro.setAddress(0x68);

    gyro.begin();
    Serial.print("Gyro Calibrating, do not move..");
    gyro.calcOffsets(0, 0);
    Serial.println("Done!");

    Wire.begin();
    Serial.begin(9600);

    Serial.println("Motor set");
}

void loop() {

    coord_ptr = AnglesGyro(10);

    Y = *(coord_ptr + 1);        // Pitch
    X = *(coord_ptr);  // Yaw
    Z = *(coord_ptr + 2);        // Roll 

    Serial.print("X: ");
    Serial.print(X);
    Serial.print("  Y: ");
    Serial.print(Y);
    Serial.print("  Z: ");
    Serial.print(Z);
    Serial.println();

    //xStepper.step(stepsPerRevolution);
}

float* AnglesGyro(int Delay) {
  gyro.update();
  static float Gyro_array[3];
  Gyro_array[0] = gyro.getAngleX();
  Gyro_array[1] = gyro.getAngleY();
  Gyro_array[2] = gyro.getAngleZ();
  delay(Delay);
  return Gyro_array;
}