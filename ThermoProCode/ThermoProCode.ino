#include "images.h"


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Data wire is plugged into pin 8 on the Arduino
#define ONE_WIRE_BUS 8


//buttons definition
#define ON_OFF 2
#define LOCK_BUTTON 3
#define UNITS 4
#define FLIP 5
#define LIGHT 6

#define LED 9

#define TIMERCOMPAREVALUE1 46875 //timer will rest after 3 sec


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//initialize state machine
enum State_e {OFF, ON, LOCK};
enum State_e gState = OFF;

//initalize temp variables
float gTempC = 0;
float gTempF = 0;

//initialize the flags but easier for me to understand as modes

char unitsmode = 0;  //mini state machine, 0 is celcius and 1 is fahrenheit
char on_off_mode = 0;  //mini state machine, 0 is off and 1 is on
char lock_mode = 0;  //mini state machine , 0 is unlocked and 1 is locked
char light_mode = 0; // 0 is off and 1 is on
char flip_mode = 0; //0 is for normal 1 is for flipped

void setup() {
  // start serial port
  Serial.begin(9600);

  // Start up the library
  sensors.begin();

  //Start the display with 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();

  pinMode(ON_OFF, INPUT);
  pinMode(LOCK_BUTTON, INPUT);
  pinMode(UNITS, INPUT);
  pinMode(LIGHT, INPUT);
  pinMode(LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ON_OFF),isr_on_off,CHANGE); //on off button interrupt
  attachInterrupt(digitalPinToInterrupt(LOCK_BUTTON),isr_lock,CHANGE); // lock button interrupt

  //start timer stuff
  noInterrupts();
  TCCR1B = 0;
  TCCR1A = 0;

  TCCR2B |= (1<<WGM21);//ctc mode
  TCCR2B |= (1<<CS22);//prescale at 1024
  TCCR2B |= (1<<CS21);
  TCCR2B |= (1<<CS20);


  OCR1A = TIMERCOMPAREVALUE1; //will reset after 3 seconds

  TIMSK1 |= (1<<OCIE1A); // attach interrupt to timer 1
  interrupts();
}

void ReadTemp(){
  sensors.begin();
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  gTempC = sensors.getTempCByIndex(0);
  gTempF = sensors.getTempFByIndex(0);
}

void Light(){
  if(digitalRead(LIGHT) && gState != OFF){
    light_mode =! light_mode;
  }
  if (light_mode){
    digitalWrite(LED,HIGH);
  }
  else{
    digitalWrite(LED,LOW);
  }
}

void Units(){
  if (flip_mode == 0){
    if (unitsmode){
      // put the celcius display
      display.drawBitmap(0,0,images[2],SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
      //set text color size and location and then print celcius value
      display.setTextColor(SSD1306_WHITE);

      display.setTextSize(2);
      display.setCursor(10,10);
       display.print(gTempC);
    }
    else{
      // put the fahrenheit display
      display.drawBitmap(0,0,images[3],SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
      //set text color size and location and then print fahrenheit value
      display.setTextColor(SSD1306_WHITE);

      display.setTextSize(2);
      display.setCursor(10,10);
      display.print(gTempF);
    }


    if (gState == LOCK){
      //lock image
      display.drawBitmap(0,0, images[0],SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
    }
    else{
      //unlock image
      display.drawBitmap(0,0, images[1],SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);

    }
    display.setRotation(0);
  }
  else{
    display.setRotation(2);
    if (unitsmode){
      // put the celcius display
      display.drawBitmap(0,0,images[2],SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
      //set text color size and location and then print celcius value
      display.setTextColor(SSD1306_WHITE);

      display.setTextSize(2);
      display.setCursor(10,10);
       display.print(gTempC);
    }
    else{
      // put the fahrenheit display
      display.drawBitmap(0,0,images[3],SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
      //set text color size and location and then print fahrenheit value
      display.setTextColor(SSD1306_WHITE);

      display.setTextSize(2);
      display.setCursor(10,10);
      display.print(gTempF);
    }


    if (gState == LOCK){
      display.drawBitmap(0,0, images[0],SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
    }
    else{
      display.drawBitmap(0,0, images[1],SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);

    }
  }
}

void OnOff(){
  if(on_off_mode){
    gState = ON;
  }
  else {
    gState = OFF;
  }
}

void CheckLock(){
  if((lock_mode == 1) && (gState != OFF)){
    gState = LOCK;
  }
}

void UnitsButton(){
  if(digitalRead(UNITS)){//if button is pressed start timer
    TCCR1B |= (1<<WGM12);//ctc
    TCCR1B |= (1<<CS12);//prescaler
    TCCR1B |= (1<<CS10);//prescaler
  }
  else{//reset timer
    TCCR1B &= (0<<WGM12);
    TCCR1B &= (0<<CS12);
    TCCR1B &= (0<<CS10);
  }
}

ISR(TIMER1_COMPA_vect){
  unitsmode = !unitsmode;
}


void CheckFlip(){
  if(digitalRead(FLIP) && gState != OFF){
    flip_mode = !flip_mode;
  }
}


void loop() {
  display.clearDisplay();
  switch(gState){
    case OFF:
      display.clearDisplay();
    break;

    case ON:
      ReadTemp();
      
      UnitsButton();
      Units();
    break;

    case LOCK:
      UnitsButton();
      Units();
    break;

  }
  Light();
  OnOff();
  display.display();
  CheckLock();
  CheckFlip();
  Serial.println(gState);
}

void isr_on_off(){
  if(digitalRead(ON_OFF)){
    on_off_mode = !on_off_mode;
  }
}

void isr_lock(){
  if(digitalRead(LOCK_BUTTON) && gState != OFF) {
    lock_mode = !lock_mode;
  }
}