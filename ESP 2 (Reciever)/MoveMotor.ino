// /workspaces/princessWinipini/ESP 2 (Reciever)/MoveMotor.ino
// princessWinipini Boat Project
// Created by calpkim & TitoSpike
// ©2025
// This code is for controlling a DC motor using an L298N motor driver with an ESP8266 NodeMCU.

/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-dc-motor-l298n-motor-driver-control-speed-direction/
*********/

// Motor A
const int ENA = D12;
const int IN1 = D14;
const int IN2 = D13; 

// Setting minimum duty cycle
int dutyCycle = 60;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {

  //Apply power to spin at maximum speed
  digitalWrite(enable1Pin, HIGH);

  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  while (dutyCycle <= 255){
    analogWrite(enable1Pin, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 60;
}