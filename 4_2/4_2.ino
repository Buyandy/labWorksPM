#define LED_MASK (1 << 2)
#define BUTTONS_MASK ((1 << 1) | (1 << 2))

long int BOTTOM = 0;
int a = 0;

void setup() {
  Serial.begin(9600);
  DDRB |= LED_MASK;
  TCCR1A = 0;
  TCCR1B = (1<<CS22);
  TCNT1 = BOTTOM;
  TIMSK1 |= (1<<TOIE2);
  DDRC &= ~BUTTONS_MASK;
  PORTC |= BUTTONS_MASK;
  PCICR |= (1<<1);
  PCMSK1 |= (1<<1) | (1<<2);
  sei();
}

ISR(TIMER1_OVF_vect) {
  if (a) {
    a = 0; 
    PORTB |= LED_MASK; 
  }
  else {
    a = 1; 
    PORTB &= ~LED_MASK;
  }
  TCNT1 = BOTTOM;
}

boolean flag1 = false;
boolean flag2 = false;

ISR(PCINT1_vect) {
  uint8_t buttonsState = PINC & BUTTONS_MASK;
  boolean state1 = !(buttonsState & (1 << 1));
  boolean state2 = !(buttonsState & (1 << 2));
  
  if (state1) { //увеличении скорости мигании
    if (!flag1) {
      flag1 = !flag1;

      if (BOTTOM+2500 < 65535) {
        BOTTOM += 2500;
      } else {BOTTOM = 0;}
      Serial.println(BOTTOM);
    } else {flag1 = !flag1;}
  }

  if (state2) { //уменьшение скорости мигании
    if (!flag2) {
      flag1 = !flag2;

      if (BOTTOM-2500 > 0) {
        BOTTOM -= 2500;
      } else {BOTTOM = 65535;}
      Serial.println(BOTTOM);
    } else {flag2 = !flag2;}
  }
}




void loop() {
  // put your main code here, to run repeatedly:
  
}
