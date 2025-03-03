// define pins for fan control and temperature sensor
#define ONOFF 2   // button to turn fan on/off
#define SPEED 3   // button to change fan speed
#define LED 9     // led indicator

// define constants for sampling and timing
#define TIMER_2_COMP_VAL 78  // timer2 compare value for 5ms sampling

// define variables for fan and temperature control
int bitSize = 14;     // bit size for SAR ADC
int sampleCount = 0;  // counter for temperature sampling
int fanSpeed = 0;     // fan speed level (0, 1, 2)
bool fanState = 0;    // fan state (on/off)

// simulated temperature sensor reading (for testing)
float temp = 3.2;

void setup() {
  Serial.begin(9600);  // start serial communication
  pinMode(LED, OUTPUT); // set led pin as output
  noInterrupts();  // disable interrupts during setup

  // configure timer1 for fan PWM control
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TCCR1A |= (1 << WGM11);  // set waveform generation mode
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1); // set compare output mode
  TCCR1B |= (1 << CS10);  // set clock source (no prescaler)

  // configure timer2 for sampling every 5ms
  TCCR2A = 0;
  TCCR2B = 0;
  OCR2A = TIMER_2_COMP_VAL;  // set compare value
  TCCR2A |= (1 << WGM21);  // set CTC mode
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  // set prescaler to 1024
  TIMSK2 |= (1 << OCIE2A);  // enable compare match interrupt

  interrupts(); // enable interrupts

  // attach external interrupts for button presses
  attachInterrupt(digitalPinToInterrupt(ONOFF), isrONOFF, RISING);
  attachInterrupt(digitalPinToInterrupt(SPEED), isrSPEED, RISING);
}

void loop() {
  // main loop is empty since everything runs on interrupts
}

// interrupt service routine for on/off button
void isrONOFF() {
  fanState = !fanState;  // toggle fan state
}

// interrupt service routine for speed button
void isrSPEED() {
  if (fanState) {  // check if fan is on
    fanSpeed = (fanSpeed + 1) % 3;  // cycle through speed levels (0,1,2)

    switch (fanSpeed) {
      case 0:
        Serial.println("Fan Speed 0");
        // analogWrite(fan, 0.3 * temp);  // set pwm to 1/3 of temperature
        break;
      case 1:
        Serial.println("Fan Speed 1");
        // analogWrite(fan, 0.6 * temp);  // set pwm to 2/3 of temperature
        break;
      case 2:
        Serial.println("Fan Speed 2");
        // analogWrite(fan, temp);  // set pwm to full temperature
        break;
    }
  }
}

// function to simulate 14-bit SAR ADC conversion
float SAR14(float Vin, float Vref) {
  // initialize variables
  float thresh;
  int bitValue;
  int result[bitSize];
  float floatResult = 0;

  // halve Vref and set threshold
  Vref /= 2;
  float initialVref = Vref;
  thresh = Vref;

  // perform SAR ADC conversion bit by bit
  for (int count = 0; count < bitSize; count++) {
    Vref /= 2;
    if (Vin >= thresh) {  // set bit to 1 if Vin is greater than threshold
      bitValue = 1;
      thresh += Vref;
    } else {  // set bit to 0 if Vin is less than threshold
      bitValue = 0;
      thresh -= Vref;
    }
    result[count] = bitValue; // store bit result
  }

  // reconstruct the float value from binary result
  for (int count = 0; count < bitSize; count++) {
    if (result[count] == 1) {
      floatResult += initialVref / pow(2, count);
    }
  }

  return floatResult;
}

// interrupt service routine to sample temperature every 5ms
ISR(TIMER2_COMPA_vect) {
  sampleCount++;

  // convert analog input to digital using SAR ADC (simulated)
  temp = SAR14(2.75, 3);

  // accumulate temperature values
  static float averageTemp = 0;
  averageTemp += temp;

  // every 1000 samples, compute and print average temperature
  if (sampleCount == 1000) {
    averageTemp /= 1000;
    Serial.println(averageTemp);
    sampleCount = 0;
    averageTemp = 0;
  }
}
