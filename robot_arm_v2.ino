#include <Stepper.h>
#include <MPU6050_light.h>
#include <Wire.h>

MPU6050 gyro(Wire);

int gyro_pin = 4;

float* coord_ptr;

int Speed = 12;
int X, Y, Z;
int init_X, init_Y, init_Z;
int dX, dY, dZ;
int dX_s, dY_s, dZ_s;

const int stepsPerRevolution = 2048;
Stepper xStepper(stepsPerRevolution, 9, 11, 10, 12);
Stepper yStepper(stepsPerRevolution, 5, 7, 6, 8);
Stepper zStepper(stepsPerRevolution, 13, 3, 2, 4); 




void setup() {

    xStepper.setSpeed(Speed);
    yStepper.setSpeed(Speed);

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

    Serial.println("Zeroing gyro");
    coord_ptr = AnglesGyro(10);
    init_X = *(coord_ptr);
    init_Y = *(coord_ptr + 1);
}

void loop() {

  coord_ptr = AnglesGyro(10);

  Y = *(coord_ptr + 1);        // Pitch
  X = *(coord_ptr);            // Roll
  Z = *(coord_ptr + 2);        // Yaw
  
  Serial.print("X: ");
  Serial.print(X);
  Serial.print("  Y: ");
  Serial.print(Y);
  Serial.print("  Z: ");
  Serial.print(Z);
  Serial.println();

  dX = (X - init_X);
  dX_s = map(dX, -180, 180, -2048, 2048);
  
  xStepper.step(dX_s);
  Serial.print("Delta X: ");
  Serial.println(dX_s);
  coord_ptr = AnglesGyro(10);

  //X = *coord_ptr;
  init_X = X;


  dY = (Y - init_Y);
  dY_s = map(dY, -180, 180, -2048, 2048);
  
  yStepper.step(dY_s);
  Serial.print("Delta Y: ");
  Serial.println(dY_s);
  coord_ptr = AnglesGyro(10);

  //Y = *coord_ptr;
  init_Y = Y;


  dZ = (Z - init_Z);
  dZ_s = map(dZ, -180, 180, -2048, 2048);

  zStepper.step(dZ_s);
  Serial.print("Delta Z: ");
  Serial.println(dZ_s);
  coord_ptr = AnglesGyro(10);

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