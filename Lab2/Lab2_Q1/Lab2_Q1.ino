#define BUTTON_1 3
#define BUTTON_2 2
#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 7

int gbutton1Count = 0;
int gbutton2Count = 0;
int gflag = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1),isr_button1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2),isr_button2,CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (gflag == 1){
    if (gbutton1Count > gbutton2Count){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED,LOW);
    digitalWrite(BLUE_LED, LOW);
    Serial.println("Red LED on");
  }else if(gbutton1Count == gbutton2Count){
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED,LOW);
    digitalWrite(BLUE_LED, HIGH);
    Serial.println("Blue LED on");
  }else if(gbutton1Count < gbutton2Count){
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(BLUE_LED, LOW);
    Serial.println("Green LED on");
  }
    gflag = 0;
  }
  
}

void isr_button1(){
  gbutton1Count +=1;
  gflag = 1;
}

void isr_button2(){
  gbutton2Count +=1;
  gflag = 1;
}