#include <SpektrumSattelite.h>

#include <Servo.h>
int m = 330;
SpektrumSattelite rx;
Servo motor_1, motor_2,motor_3,motor_4;
float motor_1_val = m, motor_2_val = m, motor_3_val = m, motor_4_val = m; 
float a,p,y, thr;
int byt = 0;
void setup()
{
  motor_1.attach(4);
  motor_2.attach(5);
  motor_3.attach(6);
  motor_4.attach(7);
  Serial.begin(115200);
  Serial3.begin(115200); //Uses Serial3 for input as default
// int ch_1 = 2, ch_2 = 3, ch_3 = 4, ch_4 = 5;
}

void loop()
{
  rx.getFrame();
  thr = rx.getThro() * .3 + 366;
  a = rx.getAile() - 486;
  p = rx.getElev() - 832;
  y = rx.getRudd() - 486;
  Serial.print(rx.getThro());
  Serial.print("\t");
  Serial.print(rx.getAile());
  Serial.print("\t");
  Serial.print(rx.getElev());
  Serial.print("\t");
  Serial.print(rx.getRudd());
  Serial.print(stepperFunction(motor_1_val));
  Serial.print("\t");
  Serial.print(stepperFunction(motor_2_val));
  Serial.print("\t");
  Serial.print(stepperFunction(motor_3_val));
  Serial.print("\t");
  Serial.print(stepperFunction(motor_4_val));
  Serial.print("\n");
  motor_1_val = thr + stepperFunction(thr) * (((a* -1) - p - y/2)/2);
  motor_2_val = thr + stepperFunction(thr) * (((a* -1) + p + y/2)/2);
  motor_3_val = thr + stepperFunction(thr) * ((a - p + y/2)/2);
  motor_4_val = thr + stepperFunction(thr) * ((a + p - y/2)/2);

  motor_1_val = motor_1_val > 770 ? 770 : motor_1_val;
  motor_2_val = motor_2_val > 770 ? 770 : motor_2_val;
  motor_3_val = motor_3_val > 770 ? 770 : motor_3_val;
  motor_4_val = motor_4_val > 770 ? 770 : motor_4_val;

  motor_1_val = motor_1_val < 330 ? thr : motor_1_val;
  motor_2_val = motor_2_val < 330 ? thr : motor_2_val;
  motor_3_val = motor_3_val < 330 ? thr : motor_3_val;
  motor_4_val = motor_4_val < 330 ? thr : motor_4_val;

  Serial.print(motor_1_val);
  Serial.print("\t");
  Serial.print(motor_2_val);
  Serial.print("\t");
  Serial.print(motor_3_val);
  Serial.print("\t");
  Serial.print(motor_4_val);
  Serial.print("\n");
  
  motor_1.write(motor_1_val);
  motor_3.write(motor_3_val);
  motor_2.write(motor_2_val);
  motor_4.write(motor_4_val);

  motor_1.writeMicroseconds(450);
  motor_3.writeMicroseconds(500);
  motor_2.writeMicroseconds(500);
  motor_4.writeMicroseconds(450);
}

float stepperFunction(float curr_pwm) 
{
  return ((770 - curr_pwm)/512);
}
