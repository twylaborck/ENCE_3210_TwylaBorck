char array[5] = {'A','B','C','D','R'};
int rCount = 0;
int gCount = 0;
int bCount = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i <5; i++){
    if (array[i] =='R'){
      Serial.println("R found");
      rCount += 1;
    }else if (array[i] == 'G'){
      Serial.println("G found");
      gCount += 1;
    }else if (array[i] =='B') {
      Serial.println("B found");
      bCount += 1;
    }

  }Serial.println(bCount);
  Serial.println(rCount);
  Serial.println(gCount);

}

void loop() {
  // put your main code here, to run repeatedly:

}
