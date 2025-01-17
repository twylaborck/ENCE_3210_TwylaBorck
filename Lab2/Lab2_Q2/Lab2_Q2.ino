#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 7
#define BUTTON 2
#define TIME 1000

volatile int gflag = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON),isr_button,CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (gflag == 0){
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED,LOW);
   digitalWrite(BLUE_LED,LOW);
  }else if (gflag == 1){
    
    Serial.println("R");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(BLUE_LED,LOW);  
    delay(TIME);

    Serial.println("RG");
    digitalWrite(GREEN_LED,HIGH);
    delay(TIME);

    Serial.println("RGB");
    digitalWrite(BLUE_LED,HIGH);
    delay(TIME);

    Serial.println("GB");
    digitalWrite(RED_LED, LOW);
    delay(TIME);

    Serial.println("B");
    digitalWrite(GREEN_LED, LOW);
    delay(TIME);

    Serial.println("RB");
    digitalWrite(RED_LED, HIGH);
    delay(TIME);

  }else if (gflag == 2){
    //digitalWrite(RED_LED,LOW);
    //digitalWrite(GREEN_LED,LOW);
    //digitalWrite(BLUE_LED,LOW);
    gflag = 0;
  }

}
void isr_button(){
  if (digitalRead(BUTTON)){
    gflag += 1;
  }
}