#include <SpektrumSatellite.h>

#include <Servo.h>
int m = 330;
SpektrumSatellite rx;
Servo motor_1, motor_2,motor_3,motor_4;
float motor_1_val = m, motor_2_val = m, motor_3_val = m, motor_4_val = m; 
int thr_step = 0, a_step = 0, p_step = 0, y_step = 0;
float a,p,y, thr;
int byt = 0;
bool Set_Flag1, Set_Flag2;

void setup()
{
  motor_1.attach(4);
  motor_2.attach(5);
  motor_3.attach(6);
  motor_4.attach(7);
  Serial.begin(115200);
  Serial3.begin(115200); //Uses Serial3 for input as default
// int ch_1 = 2, ch_2 = 3, ch_3 = 4, ch_4 = 5;

  //  Set flags to false for preconditions
  Set_Flag1 = false;
  Set_Flag2 = false; 
}

void loop()
{

  rx.getFrame();
  thr = rx.getThro() + thr_step;
  a = rx.getAile();
  p = rx.getElev();
  y = rx.getRudd();
  Serial.print(thr);
  if (Set_Flag1 == false || Set_Flag2 == false)
  {
    Serial.print("\tFLAGs de-activated\n");
      if (Set_Flag1 == false && thr >= 740)
      {
        Serial.print("\tFLAG1 activated\n");
        Set_Flag1 = true;
      }
      if(Set_Flag1 == true && thr <= 340)
      {
        Serial.print("\tFLAG2 activated\n");
        Set_Flag2 = true; 
      }
  }
  else if (Set_Flag1 == true || Set_Flag2 == true){
    Serial.print(thr);
    Serial.print("\t");
    Serial.print(a);
    Serial.print("\t");
    Serial.print(p);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    
    motor_1_val = thr + stepperFunction(thr) * (((a* -1) - p - (y/2))/2);
    motor_2_val = thr + stepperFunction(thr) * (((a* -1) + p + (y/2))/2);
    motor_3_val = thr + stepperFunction(thr) * ((a - p + (y/2))/2);
    motor_4_val = thr + stepperFunction(thr) * ((a + p - (y/2))/2);

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
}

float stepperFunction(float curr_pwm) 
{
  return ((770 - curr_pwm)/512);
}
