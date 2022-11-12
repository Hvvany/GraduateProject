
#define SIGNAL_PIN 10

void setup() {
  Serial.begin(115200);
  pinMode(SIGNAL_PIN, INPUT);
}

void loop() {
  if(digitalRead(SIGNAL_PIN) == HIGH) {
  Serial.println("Person was detected!");
 }else{
  Serial.println("NO PERSON");
}
  delay(500);
}
