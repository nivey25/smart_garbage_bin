#include <Stepper.h>

const int trigPin = 6;
const int echoPin = 7;
long duration;
int distance;
int count = 0;
bool open = false;

const int stepsPerRev = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRev, 9, 11, 10, 12);

void setup() {
  // set the speed at 60 rpm:
  // initialize the serial port:
  Serial.begin(9600);
  myStepper.setSpeed(120);
  //lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // step one revolution  in one direction:
  myStepper.step(0);
  // // delay(500);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  if (distance < 8){
    open = true;
    for(int count = 0; count < 30; count++){
      myStepper.step(stepsPerRev);
      delay(1);
      Serial.println(count);
    }
  }
   else if (open){
     myStepper.step(0);
     delay(3000);
    for(int count = 0; count < 30; count++){
      myStepper.step(-stepsPerRev);
      delay(1);
      Serial.println(count);
    }
    open = false;
  }
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
}