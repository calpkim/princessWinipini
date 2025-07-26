#define IN1 D5
#define IN2 D6
#define IN3 D7
#define IN4 D8

const int potPin = A0;
const int stepsPerRevolution = 200; // 1.8° per step
int currentStep = 0;
int targetStep = 0;
int step = 0; // <-- Global step tracker

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.println("begun");
}

void loop() {
  int potVal = analogRead(potPin);
  Serial.println(potVal);
  int angle = map(potVal, 0, 1023, 0, 360);
  targetStep = map(angle, 0, 360, 0, stepsPerRevolution);

  if (targetStep > currentStep) {
    stepForward();
    currentStep++;
  } else if (targetStep < currentStep) {
    stepBackward();
    currentStep--;
  }

  delay(5); // Controls speed
}

void stepForward() {
  step = (step + 1) % 4;
  setStep(step);
}

void stepBackward() {
  step = (step + 3) % 4; // (step - 1 + 4) % 4
  setStep(step);
}

void setStep(int step) {
  switch (step) {
    case 0:
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      break;
    case 2:
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
      break;
    case 3:
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
      break;
  }
}
