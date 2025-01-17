#define BUTTON 2

int x[10]={1,2,3,4,5,6,7,8,9,10};
int y[10] = {};

volatile int gFlag;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON),isr_button,CHANGE);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (gFlag == 1){
    for (int n=0;n<10;n++){
      y[n] = 2 * x[n]-x[n-1];
      Serial.println(y[n]);
    }
    gFlag = 0;
  }

}


void isr_button(){
  if (digitalRead(BUTTON)){
    gFlag= 1;
  }
}