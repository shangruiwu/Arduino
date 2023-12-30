const int sensorPin = A0;
const float baselineTemp = 19.0;
const int switchPin = A2; // define the pin for the switch
bool programRunning = false;

void setup() {
  Serial.begin(9600); //打开一个串口，传输速率9600比特每秒==串口监视器波特率
  for(int pinNumber = 2; pinNumber<6; pinNumber++){ //快速设置pin2-5
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }

  pinMode(A2, INPUT); // Set the switch pin as input with internal pull-up resistor
}

void loop() {
  // Check the state of the switch
  if (digitalRead(switchPin) == HIGH) {
    delay(50); // Debouncing
    if (programRunning == false) {
      // The switch is pressed and the program is not running, start the program
      Serial.println("Switch pressed. Starting program.");
      programRunning = true;
      digitalWrite(5, LOW);
    }

    else {
      // The switch is pressed and the program is running, exit the program
      Serial.println("Switch pressed. Exiting program.");
      programRunning = false;
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      delay(1000); // Add a short delay for debouncing

      return (loop);     // Terminate the program
    }
  }

  // Only run the rest of the code if the program is running
  if (programRunning == true) {
    int sensorVal = analogRead(sensorPin);
    Serial.print("Sensor Value: ");
    Serial.print(sensorVal);

    float voltage = (sensorVal / 1024.0) * 5.0;
    Serial.print(", Volts: ");
    Serial.print(voltage);

    float temperature = (voltage - 0.5) * 100;
    Serial.print(", degrees C: ");
    Serial.println(temperature);

    if (temperature < baselineTemp) {
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
    } else if (temperature >= baselineTemp + 2 && temperature <= baselineTemp + 4) {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
    } else if (temperature >= baselineTemp + 4 && temperature <= baselineTemp + 6) {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
    } else if (temperature >= baselineTemp + 6) {
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
    }

    delay(1000); // Adjust the delay as needed
  }
}
