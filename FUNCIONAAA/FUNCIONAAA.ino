#include <espnow.h>

int Sin1 = D5; //0;
int Sin2 = D6; //13;
int Sin3 = D7; //15;
int Sin4 = D8; //12;
const int receiverPin = D2;
volatile unsigned long pulseStart = 0;
volatile unsigned long pulseWidth = 0;

int dutyCycle = 0;

const int stepsPerRevolution = 200;
int currentStep = 0;
int targetStep = 0;
int steering = 0;

int returnCounter = 0;

void setup() {
  pinMode(receiverPin, INPUT);
  Serial.begin(115200);
  pinMode(Sin1, OUTPUT);
  pinMode(Sin2, OUTPUT);
  pinMode(Sin3, OUTPUT);
  pinMode(Sin4, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(receiverPin), readPulse, CHANGE);
  Serial.println("Hast Set Up ish");
}

void loop() {
  
  targetStep = map(pulseWidth, 1000, 2000, 0, 150);

  if ((abs(targetStep - currentStep) < 5) && (returnCounter == 0)) {
  } else if ((abs(targetStep - currentStep < 5) && (returnCounter > 0)) {
    if (targetStep > currentStep) {
      stepForward();
      currentStep++;
    } else if (targetStep < currentStep) {
      stepBackward();
      currentStep--;
    }
    returnCounter--;
  } else {
      if (targetStep > currentStep) {
        stepForward();
        currentStep++;
      } else if (targetStep < currentStep) {
        stepBackward();
        currentStep--;
      }
    returnCounter = 4;
  }
    
  Serial.print("             TargetStep");
  Serial.print(targetStep);
  Serial.print("             PulseWidth");
  Serial.print(pulseWidth);
  Serial.print("             CurrentStep");
  Serial.println(currentStep);

}

ICACHE_RAM_ATTR void readPulse() {
    if (digitalRead(receiverPin)==HIGH) {
        pulseStart = micros();
    } else{
        pulseWidth = micros() - pulseStart;
    }
}

void stepForward() {
  static int step = 0;
  step = (step + 1) % 4;
  setStep(step);
}

void stepBackward() {
  static int step = 0;
  step = (step + 3) % 4; // (step - 1 + 4) % 4
  setStep(step);
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
      break;}
}