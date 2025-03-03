// define variables from given info

#define bitSize 14

float Vref = 3.6;
float Vin = 3.3;
float thresh;
int count;
int bitValue;
int results[bitSize];

void setup() { 
  //start communication
  Serial.begin(9600);
}

void loop() {
  //initialize test values and run the SAR14 function
  float Vref = 3.0;
  float Vin = 2.752;
  SAR14(Vin,Vref);
  delay(1000);
}

// ADC function
void SAR14(float Vin, float Vref){
  // initialize variables
  int result[bitSize];
  float floatResult = 0;

  //set the thresh to half Vref
  Vref /= 2;
  float initialVref = Vref;
  thresh = Vref;

  // start with LSB and count through each bit
  for(int count=0; count<bitSize; count++){
    Vref /= 2;

    if (Vin >= thresh){// if Vin is greater than thresh, 1 and increase the thresh
      bitValue = 1;
      thresh += Vref;
    } else { // if Vin is less than thresh, 0 and decrease the thresh
      bitValue = 0;
      thresh -= Vref;
    }
    result[count] = bitValue; // fill in result with each bit
  }
  for(int count=0; count<bitSize; count++){// find the float result from array
    if(result[count] == 1){ //result bit 1 is 1
      // result is Vref divided by two the power of n
      floatResult = floatResult + (initialVref / (pow(2,count))); 
    }
  }
  // print float result
  Serial.println(floatResult);
}