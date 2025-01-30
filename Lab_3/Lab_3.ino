#define BUTTON 2 
#define GREEN_LED 4
#define RED_LED 5
#define LED_TIME 200 // 100 ms 


#define TIMER1_CV 31250 //1s 256 prescale 
#define TIMER2_CV 255 // 1024 prescale


volatile unsigned int gCounter = 0;
volatile unsigned char gISRFlagTimer1 = 0;
volatile unsigned int gISRFlagTimer2 = 0;

volatile bool buttonPressed = false;

void setup() {
  Serial.begin(9600);

  // initialize pins 
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
  
  // Speed of Timer1 = 62.5kHz 
  noInterrupts();
  // clear timer register
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR2A = 0;
  TCCR2B = 0;

  // set the value to be compared
  OCR1A = TIMER1_CV;
  OCR2A = TIMER2_CV;

  // initialize comparing mode
  TCCR1B |= (1<<WGM12);
  TCCR2B |= (1<<WGM22);

  // set prescalers 
  TCCR1B |= (1<<CS12);
  TCCR2B |= (1<<CS22);
  TCCR2B |= (1<<CS21);
  TCCR2B |= (1<<CS20);

  // enable timer compare interrupt
  TIMSK1 |= (1<<OCIE1A);
  TIMSK2 |= (1<<OCIE2A);

  // Enable external interrupt on INT0
  EIMSK |= (1 << INT0);

  // Trigger interrupt on any change with button
  EICRA |= (1 << ISC00);
  interrupts();
}

void loop() {
  //main task
  if (gCounter == 3) { // prints every 3 seconds 
    Serial.println("main task ");
    gCounter = 0; 
    // reset counter after 3 seconds
  }
}

ISR(TIMER1_COMPA_vect){
  // toggle the first timer every 1 second 

  gISRFlagTimer1 = ~gISRFlagTimer1;
  if(gISRFlagTimer1){
    gCounter++; // main task counter

    // turn on LEDs 
    digitalWrite(GREEN_LED, HIGH);
    delay(LED_TIME);
    digitalWrite(GREEN_LED, LOW);
  }
}

ISR(TIMER2_COMPA_vect){
  // count 6 times, 6 times will take .1 sec and is used as another prescaler
  gISRFlagTimer2++;
  if (buttonPressed){
    // 255 * 6 = 1530 Hz, got this number from jeremy

    if (gISRFlagTimer2 == 6){
      gISRFlagTimer2 = 0;
      // reset after 6 and turn on LED
      digitalWrite(RED_LED,HIGH);
    } 
  } else if (gISRFlagTimer2 == 6){
      gISRFlagTimer2 = 0;
  } else {
    digitalWrite(RED_LED,LOW);
  }
}

// ISR for button 
ISR(INT0_vect) {
  buttonPressed = digitalRead(BUTTON);
}