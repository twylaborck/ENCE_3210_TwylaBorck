
int array [50] = {0};
//volatile unsigned int arraypoint = *array
int* memoryLocation = array +50;

int secondMax (int arr[], int size){
  int max = 0, secMax = 1;
    for (int i = 0; i < size; i++){
      if (arr[i]>max){
        secMax = max;
        max = arr[i];
      }else if (arr[i] > secMax && arr[i]<max){
        secMax = arr[i];
    }
  }
  return secMax;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 1; i <51; i++){
    array [i] = i;
  }
  *memoryLocation = secondMax(array, 50);
  Serial.println(*memoryLocation);
}


void loop() {
  // put your main code here, to run repeatedly:

}
