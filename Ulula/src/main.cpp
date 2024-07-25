#include <Arduino.h>
#include <ADXL345.h>
// #include <Servo.h> // ------ Problem !!! 'Servo.h' library doesn't work with this ESP32 board ---------
#include <ESP32Servo.h>  // Solution !!!

// -------------- Objects --------------
ADXL345 accel_sensor;
// use of servo library to create the PWM signals to control the RPM of the motor
Servo ESC;

// -------------- Variables ------------
int potValue;
int potPin = A2;
int escPin = A0;

void setup(void) {

  // Initialize Serial
  Serial.begin(9600);

  // Init ADXL345
  accel_sensor.init();

  // Initialize ESC
  ESC.attach(escPin, 500, 2500); // (pin, min pulse width, max pulse width in microseconds)
}

void loop(void) 
{

  // Read potentiometer value
  potValue = analogRead(potPin); // values between 0 to 4095
  
  // map the value. 0 to 180 its connected to the 1000 to 2000 of the PWM
  potValue = map(potValue, 0, 4095, 0, 180);

  /* Serial.print("potValue: ");
  Serial.println(potValue); */

  // Send signal to ESC
  ESC.write(potValue);
/* 
  int* accelReading = accel_sensor.read();
  
  int LSB_x = accel_sensor.get_LSB_x(accelReading);
  int LSB_y = accel_sensor.get_LSB_y(accelReading);
  int LSB_z = accel_sensor.get_LSB_z(accelReading);

  float G_x = accel_sensor.get_G_y(accelReading);
  float G_y = accel_sensor.get_G_x(accelReading);
  float G_z = accel_sensor.get_G_z(accelReading);

  float accel_x = accel_sensor.get_SI_x(accelReading);
  float accel_y = accel_sensor.get_SI_y(accelReading);
  float accel_z = accel_sensor.get_SI_z(accelReading);

  Serial.printf("LSB: x=%5d y=%5d z=%5d \t ", LSB_x, LSB_y, LSB_z);
  Serial.printf("G: x=%10.3f y=%10.3f z=%10.3f \t", G_x, G_y, G_z);
  Serial.printf("SI Units: x=%.3f m/s^2, y=%.3f m/s^2, z=%.3f m/s^2\n", accel_x, accel_y, accel_z);
 */
  delay(100);
}