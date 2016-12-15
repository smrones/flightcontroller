#include <Servo.h>
#include <"Pid.h">
int value = 0;

Servo motor_1, motor_2, motor_3, motor_4;
int ch_1, ch_2, ch_3, ch_4;
  
void setup() {
  motor_1.attach(6);
  motor_3.attach(9);
  motor_2.attach(10);
  motor_4.attach(11);
}

void loop() {
  //First connect your ESC WITHOUT Arming. Then Open Serial and follo Instructions
  motor_1.writeMicroseconds(value);
  motor_3.writeMicroseconds(value);
  motor_2.writeMicroseconds(value);
  motor_4.writeMicroseconds(value);
 
  if(Serial.available()) 
    value = Serial.parseInt();    // Parse an Integer from Serial
}
