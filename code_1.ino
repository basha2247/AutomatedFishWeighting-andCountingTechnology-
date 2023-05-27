#include <HX711.h>
#include <Servo.h>

// define pin numbers
#define LOADCELL_DOUT_PIN 3
#define LOADCELL_SCK_PIN 2
#define IR_SENSOR_PIN 4
#define SERVO_PIN 5

// create objects
HX711 scale;
Servo servo;
float calibration_factor = 37.27; //put some value and adjust it through serial monitor
//servo.write(0);
void setup() {
  // initialize serial communication
  Serial.begin(9600);
 
  Serial.println("HX711 calibration");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press a,s,d,f to increase calibration factor by 10,100,1000,10000 respectively");
  Serial.println("Press z,x,c,v to decrease calibration factor by 10,100,1000,10000 respectively");
  
  // initialize load cell
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();
   long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  
  // initialize servo
  servo.attach(SERVO_PIN);
  
  // set pin mode for IR sensor
  pinMode(IR_SENSOR_PIN, INPUT);
}

void loop() {
  // read load cell value and convert to grams
  float weight = scale.get_units();
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  
  // print weight to serial monitor
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" g");
   if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
    else if(temp == 's')
      calibration_factor += 100;  
    else if(temp == 'x')
      calibration_factor -= 100;  
    else if(temp == 'd')
      calibration_factor += 1000;  
    else if(temp == 'c')
      calibration_factor -= 1000;
    else if(temp == 'f')
      calibration_factor += 10000;  
    else if(temp == 'v')
      calibration_factor -= 10000;  
    else if(temp == 't')
      scale.tare();  //Reset the scale to zero
  }
  // check if IR sensor detects fish
  if (digitalRead(IR_SENSOR_PIN) == LOW) {
    // check fish weight and move servo accordingly
    if (weight < 35) {
      servo.write(0); // move servo to left
     // delay(1000); // wait for servo to move
      //servo.write(90); // stop servo
    } else if (weight >= 85) {
      servo.write(89); // move servo to right
      //delay(1000); // wait for servo to move
      //servo.write(90); // stop servo
    }
  }
  
  // wait for a short time before reading again
  delay(0);
}
