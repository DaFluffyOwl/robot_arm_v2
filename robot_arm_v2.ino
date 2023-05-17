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

int xbound = 512, ybound = 512, zbound = 512;
int xsteps, ysteps, zsteps;

const int stepsPerRevolution = 2048;
//Stepper xStepper(stepsPerRevolution, 22, 26, 24, 28);
Stepper xStepper(stepsPerRevolution, 2, 4, 3, 5);
Stepper yStepper(stepsPerRevolution, 30, 34, 32, 36);
Stepper zStepper(stepsPerRevolution, 38, 42, 40, 44); 


int switchpin = 0;
int joy_x, joy_y;
int map_joy_x, map_joy_y;
int pot_z;
int map_pot_z;



void setup() {
  
    Serial.begin(9600);

    pinMode(switchpin, INPUT);
    pinMode(joy_x, INPUT);
    pinMode(joy_y, INPUT);
    pinMode(pot_z, INPUT);

    xStepper.setSpeed(Speed);
    yStepper.setSpeed(Speed);
    zStepper.setSpeed(Speed);

    pinMode(gyro_pin, OUTPUT);
    digitalWrite(gyro_pin, LOW);

    gyro.setAddress(0x68);

    gyro.begin();
    Serial.print("Gyro Calibrating, do not move..");
    gyro.calcOffsets(0, 0);
    Serial.println("Done!");

    Wire.begin();


    Serial.println("Motor set");

    Serial.println("Zeroing gyro");
    coord_ptr = AnglesGyro(10);

    init_X = *(coord_ptr);
    init_Y = *(coord_ptr + 1);
    init_Z = *(coord_ptr + 2);
}

void loop() {

  while(digitalRead(switchpin)){
    map_joy_x = map(analogRead(joy_x), -512, 512, -10, 10);
    xStepper.step(map_joy_x);

    map_joy_y = map(analogRead(joy_y), -512, 512, -10, 10);
    yStepper.step(map_joy_y);

    map_pot_z = map(analogRead(pot_z), 0, 1024, -10, 10);
    zStepper.step(map_pot_z);      
  }

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
  
  //xsteps += dX_s;
  /*if(xsteps > xbound || xsteps < -(xbound)){
    dX_s = 0;
  }*/
  xStepper.step(dX_s);
  Serial.print("Delta X: ");
  Serial.println(dX_s);
  coord_ptr = AnglesGyro(10);

  init_X = X;


  ysteps += dY_s;
  if(ysteps > ybound || ysteps < -(ybound)){
    dY_s = 0;
  }
  dY = (Y - init_Y);
  dY_s = map(dY, -180, 180, -2048, 2048);
  
  yStepper.step(dY_s);
  Serial.print("Delta Y: ");
  Serial.println(dY_s);
  coord_ptr = AnglesGyro(10);

  init_Y = Y;


  zsteps += dZ_s;
  if(zsteps > zbound || zsteps < -(zbound)){
    dZ_s = 0;
  }
  dZ = (Z - init_Z);
  dZ_s = map(dZ, -180, 180, -2048, 2048);

  zStepper.step(dZ_s);
  Serial.print("Delta Z: ");
  Serial.println(dZ_s);
  coord_ptr = AnglesGyro(10);

  init_Z = Z;

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