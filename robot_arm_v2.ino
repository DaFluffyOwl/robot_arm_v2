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

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 6, 10, 9, 11);




void setup() {

    myStepper.setSpeed(Speed);

    pinMode(Gyro1_pin, OUTPUT);
    digitalWrite(Gyro1_pin, LOW);

    gyro1.setAddress(0x68);

    gyro1.begin();
    gyro1.calcOffsets(0, 0);

    pinMode(Gyro2_pin, OUTPUT);
    digitalWrite(Gyro2_pin, HIGH);

    gyro2.setAddress(0x69);

    gyro2.begin();
    gyro2.calcOffsets(0, 0);

    Wire.begin();
    Serial.begin(9600);

}

void loop() {

    coord_ptr = AnglesGyro1(10);
    coord_ptr2 = AnglesGyro2(10);
    Y = *coord_ptr2;        // Pitch
    X = *(coord_ptr2 + 2);  // Yaw
    Z = *coord_ptr;         // Roll 

    myStepper.step(stepsPerRevolution);
    delay(200);
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

float* AnglesGyro2(int Delay) {
  gyro2.update();
  static float Gyro_array[3];
  Gyro_array[0] = gyro2.getAngleX();
  Gyro_array[1] = gyro2.getAngleY();
  Gyro_array[2] = gyro2.getAngleZ();
  delay(Delay);
  return Gyro_array;
}