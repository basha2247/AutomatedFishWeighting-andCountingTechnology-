// Define the pin numbers for the IR sensor and LED
const int irPin = 2;
const int IRPIN=3;

// Define variables to keep track of the current and previous IR sensor-1 readings
int currentIRReading1 = 0;
int previousIRReading1 = 0;

// Define variables to keep track of the current and previous IR sensor-2 readings
int currentIRReading2 = 0;
int previousIRReading2 = 0;

// Define a variable to keep track of the count
int count1 = 0;
int count2 = 0;

// This function increments the count if the IR sensor has detected an object
void incrementCount() {
  if (currentIRReading1 == 1 && previousIRReading1 == 0) {
    count1++;
  }
  
  if (currentIRReading2 == 1 && previousIRReading2 == 0) {
    count2++;
  }

  Serial.print(" small Fish Count  : ");
  Serial.print(count1);
  Serial.print("  big Fish Count  : ");
  Serial.print(count2);
  Serial.println();
  delay(0);
}

void setup() {
  // Initialize the IR sensor-1 pin as an input
  pinMode(irPin, INPUT);
  // Initialize the IR sensor-2 pin as an input
  pinMode(IRPIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Read the current IR sensor reading
  currentIRReading1 = digitalRead(irPin);
  currentIRReading2 = digitalRead(IRPIN);

  // Increment the count if the IR sensor-1 has detected an object
  incrementCount();
  
  // Update the previous IR sensor reading
  previousIRReading1 = currentIRReading1;
  previousIRReading2 = currentIRReading2;
}