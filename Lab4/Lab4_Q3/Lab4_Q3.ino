// incude needed libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// define display perimeters
#define SCREEN_WIDTH 128   // OLED display width in pixels
#define SCREEN_HEIGHT 32   // OLED display height in pixels
#define OLED_RESET     -1  // Reset pin (-1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // OLED I2C address (0x3D for 128x64, 0x3C for 128x32)

// initialize the OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define Vref 2.5  // Voltage threshold for switching power sources
//define pins of real world analog inputs
#define SOLAR_INPUT
#define BATTERY_INPUT 

// initialize variables
float solarVoltage;
float batteryVoltage;

//initialize state machine
enum STATE{SOLAR, BATTERY, CHARGE};
char gState = SOLAR;

void setup() {
  Serial.begin(9600); // start serial communication

  // initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) ; // dont proceed loop further
  }

  display.display();  // Show Adafruit splash screen
  delay(2000);        // Pause for 2 seconds
  display.clearDisplay(); // Clear display buffer

  //if using real components define inputs 
  // pinMode(SOLAR_INPUT, INPUT);
  // pinMode(BATTERY_INPUT, INPUT);
}

void loop() {
  display.clearDisplay(); // clear previous display content

  // read voltage from the battery and solar panel if real components are present
  // batteryVoltage = analogRead(BATTERY_INPUT) * (some conversion factor);
  // solarVoltage = analogRead(SOLAR_INPUT) * (some conversion factor);
  
  //initialize random number to test code
  batteryVoltage = 2.6;
  solarVoltage = 2.4;

  switch(gState){
    case SOLAR:
    if(solarVoltage < Vref){// if the solar battery is less that 2.5 V
      gState = BATTERY; //use the battery
    }
    //display state
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);            
    display.setCursor(10, 10); 
    display.print("Solar Supply");
    break;
    

    case BATTERY:
    //check to see if solar voltage is above 2.5V
    if(solarVoltage >= Vref){// it is so go back to using solar supply
      gState = SOLAR;
    }
    else if (solarVoltage > batteryVoltage){ // the voltage isnt above 2.5 but its bigger than battery
      gState = CHARGE;
    }
    //display state
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);            
    display.setCursor(10, 10); 
    display.print("Battery Supply");
    break;

    case CHARGE:
    if(batteryVoltage > solarVoltage){// battery is more charged than solar so use battery
      gState = BATTERY;
    }
    //display state
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);            
    display.setCursor(10, 10); 
    display.print("Charging Battery");
    break;
  }
  //update display
  display.display();
}