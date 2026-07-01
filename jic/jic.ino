int Sin1 = 5; //0;
int Sin2 = 6; //13;
int Sin3 = 7; //15;
int Sin4 = 8; //12;
int dutyCycle = 0;
const int stepsPerRevolution = 200; // 1.8° per step
int currentStep = 0;
int targetStep = 0;
int steering = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(Sin1, OUTPUT);
  pinMode(Sin2, OUTPUT);
  pinMode(Sin3, OUTPUT);
  pinMode(Sin4, OUTPUT);
  Serial.begin(115200);
  Serial.println("Setup Complete");

}

void loop() {
  Serial.println("Looped!");
  delay(1000);
  return;
  // put your main code here, to run repeatedly:
  int angleSteering = map(steering, 0, 1023, 0, 360);
  targetStep = map(angleSteering, 0, 360, 0, stepsPerRevolution);
  Serial.println(targetStep);
    if (targetStep > currentStep) {
    stepForward();
    currentStep++;
    } else if (targetStep < currentStep) {
    stepBackward();
    currentStep--;
    }
  delay(5); // Controls speed
  steering++;
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