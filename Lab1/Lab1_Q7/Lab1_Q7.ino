#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 7
#define BUTTON_1 2
#define BUTTON_2 3
#define TIME 1000


int array1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int array2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int array3[10];

int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BUTTON_1)){
    delay(TIME);
    counter += 1;
    delay(TIME);

    if (counter == 1) {

      Serial.print("Counter: ");
      Serial.println(counter);
      Serial.println("Red LED on");
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BLUE_LED, LOW);
      delay(TIME);

    } else if (counter == 2) {

      Serial.print("Counter: ");
      Serial.println(counter);      
      Serial.println("Green LED on");
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED,HIGH);
      digitalWrite(BLUE_LED, LOW);
      delay(TIME);


    } else if (counter == 3) {

      Serial.print("Counter: ");
      Serial.println(counter);      
      Serial.println("Blue LED on");
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BLUE_LED, HIGH);
      delay(TIME);

    } else {
      counter = 0;

      Serial.print("Counter: ");
      Serial.println(counter);      
      Serial.println("All LED off");
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BLUE_LED, LOW);
      delay(TIME);

    }
  }

  if (digitalRead(BUTTON_2)) {
      Serial.println("Calculating...");
      Serial.println("All LED off");
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BLUE_LED, LOW);
      delay(TIME);

      for (int i = 0; i < 10; i++) {
        if (counter == 1) { 

          array3[i] = array1[i] + array2[i];

        } else if (counter == 2) { 

          array3[i] = array1[i] - array2[i];

        } else if (counter == 3) {

          array3[i] = array1[i] * array2[i];

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
        Serial.println(array3[i]);
      }

    
  }
}