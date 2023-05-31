int switchState = 0; // status of the button switch
boolean firstRun = true;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(3, OUTPUT); // green led
  pinMode(4, OUTPUT); // yellow led
  pinMode(5, OUTPUT); // red led
  pinMode(2, INPUT); // switch (button)
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(2);

  int redLED = digitalRead(5);
  int yellowLED = digitalRead(4);
  int greenLED = digitalRead(3);

  if (firstRun == true) {
    Serial.println("Power on...");
    firstRun = false;
  }

  if (switchState == LOW) {
    // button unpressed
    
    digitalWrite(3, HIGH); // green

    digitalWrite(4, LOW); // yellow
    digitalWrite(5, LOW); // red

  } else {
    // button pressed

    digitalWrite(3, LOW); // green

    digitalWrite(4, LOW); // yellow
    digitalWrite(5, HIGH); // red
    Serial.println("Launching!");
    delay(250);
    digitalWrite(4, HIGH); // yellow
    digitalWrite(5, LOW); // red
    delay(250);
  }
  if (yellowLED == HIGH) {
    Serial.println("(yellow on)");
  }
  // if (redLED == HIGH) {
  //   Serial.println("(red on)");
  // }
  
}
