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
  for(angle = 0; angle < 103; angle++){
    servo.write(angle);
    delay(30);
  }
  for(angle = 103; angle > 0; angle--){
    servo.write(angle);
    delay(30);
}
}
