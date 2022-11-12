#include <Servo.h>

Servo servo;
int servoPin = 9;
int angle = 0;

void setup() {
  servo.attach(servoPin);
  servo.write(angle);
}


void loop() {
  servo.write(angle);
  for(angle = 0; angle < 100; angle=angle+20){
    servo.write(angle);
    delay(1000);
  }
  for(angle = 100; angle > 0; angle=angle-20){
    servo.write(angle);
    delay(1000);
  }
}
