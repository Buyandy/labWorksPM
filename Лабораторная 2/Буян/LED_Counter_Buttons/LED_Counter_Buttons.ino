#define BUTTONS_MASK ((1 << 1) | (1 << 2) | (1 << 3))
#define LEDS_MASK    ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5))

НОВЫЙ СКЕТЧ

byte counter = 0;

unsigned long lastDebounceTime[3] = {0, 0, 0};
const unsigned long debounceDelay = 250;
boolean _flag = true;

void setup() {
  Serial.begin(9600);
  DDRB |= LEDS_MASK;
  DDRC &= ~BUTTONS_MASK;
  PORTC |= BUTTONS_MASK;
  PORTB &= ~LEDS_MASK;
}

void loop() {
  uint8_t buttonsState = PINC & BUTTONS_MASK;
  
  boolean incState = !(buttonsState & (1 << 1));
  boolean decState = !(buttonsState & (1 << 2));
  boolean rstState = !(buttonsState & (1 << 3));
  
  if (_flag && incState && (millis() - lastDebounceTime[0] > debounceDelay)) {
    _flag = false;
    lastDebounceTime[0] = millis();
    if (counter < 15) counter++;
    else counter = 0;
    updateLedsReg();
    printToSerial();
  }
  
  if (_flag && decState && (millis() - lastDebounceTime[1] > debounceDelay)) {
    _flag = false;
    lastDebounceTime[1] = millis();
    if (counter > 0) counter--;
    else counter = 15;
    updateLedsReg();
    printToSerial();
  }
  
  if (_flag && rstState && (millis() - lastDebounceTime[2] > debounceDelay)) {
    _flag = false;
    lastDebounceTime[2] = millis();
    counter = 0;
    updateLedsReg();
    printToSerial();
  }

  if ((incState | decState | rstState) == false) _flag = 1;
}


void updateLedsReg() {
  PORTB &= ~LEDS_MASK;
  PORTB |= (counter << 2) & LEDS_MASK; 
}


void printToSerial() {
  Serial.print("Counter (bin): ");
  Serial.println(counter, BIN);
  Serial.print("Counter (dec): ");
  Serial.println(counter);
}