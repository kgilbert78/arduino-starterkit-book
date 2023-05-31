const int sensorPin = A0; // int is accurate due to it's value. kind of like a variable - prints out as 14 not A0
const float baselineTemperature = 20.3; // check current air temperature and update this before use. 
// would be better to have 2nd temperature sensor and assign it's reading to baselineTemp each time through the loop.

void setup() {
  // put your setup code here, to run once:

  // open serial port connection to board at speed 9600 (same as baud rate)
  Serial.begin(9600); 

  // assign output mode to all 3 pins and start all 3 as "off" (low)
  for (int pinNumber = 2; pinNumber<5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(sensorPin);

  int sensorValue = analogRead(sensorPin);
  Serial.print("Sensor value: ");
  Serial.print(sensorValue); // between 0-1023 & represents voltage on pin

  // convert ADC reading to voltage
  float voltage = (sensorValue/1024.0)*5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  // convert to degrees celcius with offset for below zero: 10 milivolts change in sensor == 1 degree celsius
  float temperature = (voltage-0.5)*100;
  Serial.print(", Degrees Celsius: ");
  Serial.println(temperature);

  // output:
  // Sensor value: 153, Volts: 0.75, Degrees Celsius: 24.71


  // // their suggested code
  // if (temperature < baselineTemperature+2) {
  //   digitalWrite(2, LOW);
  //   digitalWrite(3, LOW);
  //   digitalWrite(4, LOW);
  // } else if (temperature >= baselineTemperature+2 && temperature < baselineTemperature+4) {
  //   digitalWrite(2, HIGH);
  //   digitalWrite(3, LOW);
  //   digitalWrite(4, LOW);
  // } else if (temperature >= baselineTemperature+4 && temperature < baselineTemperature+6) {
  //   digitalWrite(2, HIGH);
  //   digitalWrite(3, HIGH);
  //   digitalWrite(4, LOW);
  // } else if (temperature >= baselineTemperature+6) {
  //   digitalWrite(2, HIGH);
  //   digitalWrite(3, HIGH);
  //   digitalWrite(4, HIGH);
  // }


  // my code

  const int pins [3] = {2, 3, 4};
  const float temperatureRange [3] = {baselineTemperature+2, baselineTemperature+4, baselineTemperature+6};

  // for the pin whose index matches the temperatureRange index, if the temperature reading is greater than the temperature at that index, turn the light on
  for (int tempIndex = 0; tempIndex < 3; tempIndex++) {

    for (int pinIndex = 0; pinIndex < 3; pinIndex++) {
      
      if (pinIndex == tempIndex) {
        Serial.print("index ");
        Serial.print(tempIndex);
        Serial.print(": ");
        Serial.print(temperature);
        Serial.print(" vs ");
        Serial.println(temperatureRange[tempIndex]);

        // output:
        // index 0: 24.71 vs 22.30
        // index 1: 24.71 vs 24.30
        // index 2: 24.71 vs 26.30

        if (temperature < temperatureRange[tempIndex]) {
          digitalWrite(pins[pinIndex], LOW);
        } else {
          digitalWrite(pins[pinIndex], HIGH);
        }

      }

    }

  }
  delay(1); // would it be better to distribute delays between each for loop? doesn't seem to make a noticable difference.
  // delay(400);  // to read the output
}
