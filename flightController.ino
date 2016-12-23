#include <Servo.h>
int value = 0;

Servo motor_1, motor_2, motor_3, motor_4;
int ch_1 = 2, ch_2 = 3, ch_3 = 4, ch_4 = 5;
  
void setup() {
  Serial.begin(9600);
  pinMode(ch_1, INPUT);
  pinMode(ch_2, INPUT);
  pinMode(ch_3, INPUT);
  pinMode(ch_4, INPUT);
  
  motor_1.attach(6);
  motor_3.attach(7);
  motor_2.attach(8);
  motor_4.attach(9);
}

void loop() {
  //First connect your ESC WITHOUT Arming. Then Open Serial and follo Instructions
  // old way of writing microseconds to value range 1100 - 2000
//  motor_1.writeMicroseconds(value);
//  motor_3.writeMicroseconds(value);
//  motor_2.writeMicroseconds(value);
//  motor_4.writeMicroseconds(value);

// current way of outputing value to the motors.
// range ~330 to ~770
 motor_1.write(map(value,0,1023,0,179));
  motor_2.write(map(value,0,1023,0,179));
   motor_3.write(map(value,0,1023,0,179));
    motor_4.write(map(value,0,1023,0,179)); 

  // gets value from serial monitor (not reciever inputs)
  if(Serial.available()) 
    value = Serial.parseInt();    // Parse an Integer from Serial

//value = digitalRead(inPin)
}
