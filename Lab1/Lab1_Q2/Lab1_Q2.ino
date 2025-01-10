#include <math.h>
double array[360] = {0};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  for (int i = 0; i <361; i++){
    array [i] = cos(i*DEG_TO_RAD);
    Serial.println(array[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
