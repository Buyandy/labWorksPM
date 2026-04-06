
void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  for(int i = 10; i <= 13; i++) {
    digitalWrite(i, LOW);
    delay(200);
    digitalWrite(i, HIGH);
  }
}
