
void setup() {
  DDRB |= 0b111100;
}

void loop() {
  PORTB &= ~(1 << 2);

  delay(500);
  PORTB |= (1 << 2);

  delay(500);
}
