#include <Stepper.h>
const int receiverPin = 2;
volatile unsigned long pulseStart = 0;
volatile unsigned long pulseWidth = 0;
/*
int Sin1 = 5; //0;
int Sin2 = 6; //13;
int Sin3 = 7; //15;
int Sin4 = 8; //12;
int dutyCycle = 0;

int steering = 0;

*/
int currentStep = 0;
int targetStep = 0;
const int stepsPerRevolution = 200; // 1.8° per step
Stepper mystepper(stepsPerRevolution, 5, 6, 7, 8);


void setup() {
    Serial.begin(9600);
    pinMode(receiverPin, INPUT);
    /*Serial.begin(115200);
    pinMode(Sin1, OUTPUT);
    pinMode(Sin2, OUTPUT);
    pinMode(Sin3, OUTPUT);
    pinMode(Sin4, OUTPUT);
    analogWriteRange(100); */
    mystepper.setSpeed(30);
    attachInterrupt(digitalPinToInterrupt(receiverPin), readPulse, CHANGE);
}

void loop() {
 //   Serial.print("PulseWidth               ");
 //  Serial.println(steering);
 //   Serial.println("us");
    
    targetStep = map(pulseWidth, 996, 1996, 0, 50);
    mystepper.step(5000);
    currentStep = targetStep;
    Serial.print(targetStep);
    Serial.print("             ");
    Serial.println(currentStep);
    /*
    steering = (pulseWidth + 8)/10 * 10;
    int angleSteering = map(steering, 996, 1996, 0, 360);
    targetStep = map(angleSteering, 0, 360, 0, stepsPerRevolution);
    

    if (abs(targetStep - currentStep) < 5) {
    } else {
        while (currentStep != targetStep) {
          if (targetStep > currentStep) {
          stepForward();
          currentStep++;
          } else if (targetStep < currentStep) {
          stepBackward();
          currentStep--;
          }
        delay(5);
        }
    }
    */

}

void readPulse() {
    if (digitalRead(receiverPin)==HIGH) {
        pulseStart = micros();
    } else{
        pulseWidth = micros() - pulseStart;
    }
}
/*
void stepForward() {
/*  static int step = 0;
  step = (step + 1) % 4;
  setStep(step);
  
  setStep(currentStep % 4);
}

void stepBackward() {
  setStep(currentStep % 4);
}

void setStep(int step) {
  switch (step) {
    case 0:
      digitalWrite(Sin1, HIGH); digitalWrite(Sin2, LOW);
      digitalWrite(Sin3, HIGH); digitalWrite(Sin4, LOW);
      break;
    case 1:
      digitalWrite(Sin1, LOW); digitalWrite(Sin2, HIGH);
      digitalWrite(Sin3, HIGH); digitalWrite(Sin4, LOW);
      break;
    case 2:
      digitalWrite(Sin1, LOW); digitalWrite(Sin2, HIGH);
      digitalWrite(Sin3, LOW); digitalWrite(Sin4, HIGH);
      break;
    case 3:
      digitalWrite(Sin1, HIGH); digitalWrite(Sin2, LOW);
      digitalWrite(Sin3, LOW); digitalWrite(Sin4, HIGH);
      break;
  }
}
*/