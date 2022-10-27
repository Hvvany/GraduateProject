#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //블루투스의 Tx, Rx핀을 2번 3번핀으로 설정
int a= 0;
void setup() {
    Serial.begin(9600);
    mySerial.begin(9600); // baud rate 9600으로 설정
}
void loop() {
    mySerial.println(a); // 블루투스 시리얼에 입력
    a++;
    delay(500);
}
