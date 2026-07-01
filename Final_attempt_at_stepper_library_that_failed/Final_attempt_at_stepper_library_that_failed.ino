// Read PWM signals from FS-iA6B using Arduino Uno
#include <espnow.h>
#include <Stepper.h>
const int receiverPin = D2;
volatile unsigned long pulseStart = 0;
volatile unsigned long pulseWidth = 0;
long currentStep = 0;
long targetStep = 300;
const int stepsPerRevolution = 200;
Stepper mystepper(stepsPerRevolution, D5, D6, D7, D8);

void setup() {
    pinMode(receiverPin, INPUT);
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(receiverPin), readPulse, CHANGE);
}

void loop() {
    targetStep = map(pulseWidth, 1000, 2000, 0, 200);
    if (abs(targetStep - currentStep) < 5) {
        Serial.println("no");
    } else {
        int difference = targetStep - currentStep;
        Serial.print("Moving steps: "); Serial.println(difference);
        mystepper.step(difference);
        currentStep = targetStep;
        Serial.println("Done");
    }
    
    Serial.print("TargetStep");
    Serial.print(targetStep);
    Serial.print("    CurrentStep    ");
    Serial.print(currentStep);
    Serial.print("    PulseWidth    ");
    Serial.println(pulseWidth);
    delay(1000);
}

ICACHE_RAM_ATTR void readPulse() {
    if (digitalRead(receiverPin)==HIGH) {
        pulseStart = micros();
    } else{
        pulseWidth = micros() - pulseStart;
    }
}