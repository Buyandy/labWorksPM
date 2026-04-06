int led = 1;

void setup() {
  DDRB |= 0b111100;
}

void loop() {
  led = led << 1;
  
  if (led & (1<<4)) {
    led = 1;
  }
  
  PORTB = ~(led << 2);

  delay(200);
}
