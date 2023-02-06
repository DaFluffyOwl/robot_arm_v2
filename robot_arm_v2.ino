#include <Stepper.h>
#include <MPU6050_light.h>
#include <Wire.h>

MPU6050 gyro1(Wire);
MPU6050 gyro2(Wire);

int Gyro1_pin = 4;
int Gyro2_pin = 5;

float* coord_ptr;
float* coord_ptr2;

int Speed = 12;
int X, Y, Z;

const int stepsPerRevolution = 2048;
Stepper xStepper(stepsPerRevolution, 6, 10, 9, 11);




void setup() {

    xStepper.setSpeed(Speed);

    pinMode(Gyro1_pin, OUTPUT);
    digitalWrite(Gyro1_pin, LOW);

    gyro1.setAddress(0x68);

    gyro1.begin();
    Serial.print("Gyro Calibrating, do not move..");
    gyro1.calcOffsets(0, 0);
    Serial.println("Done!");

    Wire.begin();
    Serial.begin(9600);

    Serial.println("Motor set");
}

void loop() {

    coord_ptr = AnglesGyro1(10);

    Y = *(coord_ptr + 1);        // Pitch
    X = *(coord_ptr);  // Yaw
    Z = *(coord_ptr + 2);         // Roll 
    Serial.print("X:");
    Serial.println(X);

    //xStepper.step(stepsPerRevolution);
}

float* AnglesGyro1(int Delay) {
  gyro1.update();
  static float Gyro_array[3];
  Gyro_array[0] = gyro1.getAngleX();
  Gyro_array[1] = gyro1.getAngleY();
  Gyro_array[2] = gyro1.getAngleZ();
  delay(Delay);
  return Gyro_array;
}