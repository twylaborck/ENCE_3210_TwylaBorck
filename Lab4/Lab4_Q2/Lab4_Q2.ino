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
#define SOLAR
#define BATTERY 

// initialize variables
float solarVoltage;
float batteryVoltage;

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
  // pinMode(SOLAR, INPUT);
  // pinMode(BATTERY, INPUT);
}

void loop() {
  display.clearDisplay(); // clear previous display content

  // read voltage from the battery and solar panel if real components are present
  // batteryVoltage = analogRead(BATTERY) * (some_conversion_factor);
  // solarVoltage = analogRead(SOLAR) * (some_conversion_factor);
  
  //initialize random number to test code
  batteryVoltage = 2.6;
  solarVoltage = 2.4;

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);            
  display.setCursor(10, 10);          

  //power source selection
  if (solarVoltage > Vref) { // if solar voltage is above 2.5V, use solar power
    display.print("Solar Supply");
  } else {//solar voltatage is less than 2.5V
    if (batteryVoltage < solarVoltage) {// battery voltage is lower than solar voltage, charge battery
      display.print("Charging Battery");
    } 
    else { // use battery power
      display.print("Battery Supply");
    }
  }

  display.display(); // update display
}
