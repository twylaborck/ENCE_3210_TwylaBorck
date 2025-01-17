#define RED_LED 5
#define GREEN_LED 4
#define PATTERN_LENGTH 3

int count = 0;

char array [10] = {'A','C','R','G','B','L','Z','R','G','S'};
char pattern [PATTERN_LENGTH] = {'R','G','B'};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  for (int i = 0; i <= 10 - PATTERN_LENGTH; i++){
    int match = 1;
    for (int j = 0; j < PATTERN_LENGTH; j++) {
      if (array[i+j] != pattern[j]) {
        match = 0;
        break;
      }
    }
    if (match == 1) {
      count +=1;
    }
  }
  if (count > 0){
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
  else{
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
  Serial.print(F("Pattern count"));
  Serial.println(count);

}

void loop() {
  // put your main code here, to run repeatedly:

}
