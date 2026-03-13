/****************** code made by PARTH SANTOSH KUNNIR************/
// code source: https://www.instructables.com/DIY-SOIL-MOISTURE-SENSOR-CHEAP-YET-ACCURATE-/

int moistPin = A0; // moisture sensor is connected to analog pin A0
int moistVal = 0; // set up variable to store moisture value from sensor
int led = 9; // LED pin

void setup()
{
  Serial.begin(9600); // start serial communication at 9600 baud rate
}
void loop()
{
  moistVal = analogRead(moistPin);
  // Serial.println(moistVal); // raw value from sensor
  // not sure where they got this formula from but it seems to work pretty well for my soil moisture sensor, the probes are about 1 - 1.5 inches apart and the sensor is calibrated for that distance
  int percent = 2.718282 * 2.718282 * (.008985 * moistVal + 0.207762); //calculate percent for probes about 1 - 1.5 inches apart
  Serial.println(percent); // percent moisture value is printed to the serial monitor, you can use this value to set up a threshold for watering your plants, I have mine set to 50% so when the soil moisture is below 50% my led will turn on and when it is above 50% the led will turn off
  // Serial.println("% Moisture "); // 
  if(percent<50)
  {digitalWrite(led,HIGH);} // if the sensor value is below 50% led will glow to indicate that the soil is dry and needs watering
  
  else
  {digitalWrite(led,LOW);} // if sensor value is above 50% led on your nano will turn off

  delay(250); // for stability 
}
