#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 7
#define BUTTON_1 2
#define BUTTON_2 3
#define TIME 500


int gArray1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int gArray2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int gArray3[10];

int gCounter = 0;

volatile int button1Flag = 0;
volatile int button2Flag = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2),isr_button2, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (button1Flag == 1){
    delay(TIME);
    gCounter += 1;
    if (gCounter == 1) {

      Serial.print("Counter: ");
      Serial.println(gCounter);
      Serial.println("Red LED on");
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BLUE_LED, LOW);
      delay(TIME);

    } else if (gCounter == 2) {

      Serial.print("Counter: ");
      Serial.println(gCounter);      
      Serial.println("Green LED on");
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED,HIGH);
      digitalWrite(BLUE_LED, LOW);
      delay(TIME);

    } else if (gCounter == 3) {

      Serial.print("Counter: ");
      Serial.println(gCounter);      
      Serial.println("Blue LED on");
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BLUE_LED, HIGH);
      delay(TIME);

    } else {
      gCounter = 0;

      Serial.print("Counter: ");
      Serial.println(gCounter);      
      Serial.println("All LED off");
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BLUE_LED, LOW);
      delay(TIME);
    }
    button1Flag = 0;
  }

  if (button2Flag == 1) {
    Serial.println("Calculating...");
    Serial.println("All LED off");
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED,LOW);
    digitalWrite(BLUE_LED, LOW);
    delay(TIME);

    for (int i = 0; i < 10; i++) {
      if (gCounter == 1) { 

        gArray3[i] = gArray1[i] + gArray2[i];

      } else if (gCounter == 2) { 

        gArray3[i] = gArray1[i] - gArray2[i];

      } else if (gCounter == 3) {

        gArray3[i] = gArray1[i] * gArray2[i];

      }
    }

    
    Serial.println("All LED on");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(BLUE_LED, HIGH);
    delay(TIME);

    for (int i = 0; i < 10; i++) {
      Serial.print("array3");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(gArray3[i]);
      }

  button2Flag = 0;
  }
}

void isr_button1(){
  if (digitalRead(BUTTON_1)){
    button1Flag= 1;
  }
}

void isr_button2(){
  if (digitalRead(BUTTON_2)){
    button2Flag= 1;
  }
}