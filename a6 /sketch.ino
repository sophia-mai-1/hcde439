// Define connection pins:
const int pir = 9;
const int button = 13;
const int wled = 10;
const int bled = 11;

// Create variables:
int pval = 0;
int bval = 0;
bool motionState = false; // We start with no motion detected.
bool buttonState = false;

void setup() {
  // Configure the pins as input or output:
  pinMode(wled, OUTPUT);
  pinMode(bled, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(button, INPUT);

  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
}

void loop() {
  // Read out the pirPin and store as val:
  pval = digitalRead(pir);
  bval = digitalRead(button);
  Serial.println(pval);
  Serial.println(bval);

  // If motion is detected (pirPin = HIGH), do the following:
  if (pval == HIGH && bval == HIGH) {
    digitalWrite(wled, HIGH); // Turn on the on-board LED.
    digitalWrite(bled, HIGH); // Turn on the on-board LED.


    // Change the motion state to true (motion detected):
    if (motionState == false) {
      // Serial.println("Motion detected!");
      // Serial.println(val);
      motionState = true;
    }

    if (buttonState == false) {
      buttonState = true;
    }
  }

  // If no motion is detected (pirPin = LOW), do the following:
  else if (pval == HIGH && bval == LOW){
    analogWrite(wled, 50); // Turn off the on-board LED.
    digitalWrite(bled, LOW);

    // Change the motion state to false (no motion):
    if (buttonState == true) {
      // Serial.println("Motion ended!");
      buttonState = false;
    }
  }

    else if (pval == LOW && bval == HIGH){
    analogWrite(bled, 50); // Turn off the on-board LED.
    digitalWrite(wled, LOW); // Turn off the on-board LED.


    //  Change the motion state to false (no motion):
    if (buttonState == true) {
      // Serial.println("Motion ended!");
      buttonState = false;
    }
  }

  else {
    digitalWrite(wled, LOW); 
    digitalWrite(bled, LOW);

  }
}