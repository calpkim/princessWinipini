#include <Stepper.h>
const int receiverPin = 11;
volatile unsigned long pulseStart = 0;
volatile unsigned long pulseWidth = 0;
int currentStep = 0;
int targetStep = 25;
const int stepsPerRevolution = 200;
Stepper mystepper(stepsPerRevolution, 5, 6, 7, 8);

void setup() {
    Serial.begin(9600);
    pinMode(receiverPin, INPUT);
    mystepper.setSpeed(30);
    attachInterrupt(digitalPinToInterrupt(receiverPin), readPulse, CHANGE);
}

void loop() {
    targetStep = map(pulseWidth, 996, 1996, 0, 50);
    if (-5 < targetStep - currentStep < 5) {
    } else {
    mystepper.step(targetStep - currentStep);
    currentStep = targetStep;
    }
    Serial.print(targetStep);
    Serial.print("             ");
    Serial.println(currentStep);

}

void readPulse() {
    if (digitalRead(receiverPin)==HIGH) {
        pulseStart = micros();
    } else{
        pulseWidth = micros() - pulseStart;
    }
}