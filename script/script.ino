// Define Receiver Input Connections
#define CH1 3
#define CH2 5
#define CH3 6
#define CH4 9
#define CH5 12
#define CH6 13


// Define Motor Connections
#define motorPin1 10
#define motorPin2 11



// Integers to represent values from sticks and pots
// int ch1Value;
// int ch2Value;
int ch3Value;
// int ch4Value;
bool ch5Value;
bool ch6Value;
// Boolean to represent switch value




void setup() {
  // Set up serial monitor
  Serial.begin(9600);

  // pinMode(CH1, INPUT);
  // pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  // pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}


void loop() {
  readInput();

  if(ch5Value){
    if(ch3Value > 0){
      forward();
    }
    else{
      backward();
    }
  }
  else{
    stop();
  }


}


void stop(){
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 0);
}


void forward(){
  analogWrite(motorPin1, ch3Value);
  analogWrite(motorPin2, 0);
}


void backward(){
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, -ch3Value);
}


// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int inputMin, int inputMax, int outputMin, int outputMax, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  ch = map(ch, inputMin, inputMax, outputMin, outputMax);
  return constrain(ch, outputMin, outputMax);
}

int readChannelRaw(int channelInput) {
  return pulseIn(channelInput, HIGH, 30000);
}

// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 1000, 2000, 0, 100, intDefaultValue);
  return (ch > 50);
}

void readInput() {
  // Get values for each channel
  // ch1Value = readChannelRaw(CH1, 0, 256, 0);
  // ch2Value = readChannelRaw(CH2, 0, 256, 0);
  ch3Value = readChannel(CH3, 1000, 1800, -255, 255, 0);
  // ch4Value = readChannelRaw(CH4, 0, 256, 0);
  ch5Value = readSwitch(CH5, 0);
  ch6Value = readSwitch(CH6, 0);

  // Print to Serial Monitor
  // Serial.print("Ch1: ");
  // Serial.print(ch1Value);
  // Serial.print(" | Ch2: ");
  // Serial.print(ch2Value);
  Serial.print("Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" | ");
  Serial.print(readChannelRaw(CH3));
  // Serial.print(" | Ch4: ");
  // Serial.print(ch4Value);
  Serial.print(" | Ch5: ");
  Serial.print(ch5Value);
  Serial.print(" | Ch6: ");
  Serial.println(ch6Value);
}