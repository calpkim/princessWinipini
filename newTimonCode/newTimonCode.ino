// Read PWM signals from FS-iA6B using Arduino Uno
const int receiverPin = 2;
volatile unsigned long pulseStart = 0;
volatile unsigned long pulseWidth = 0;
int Sin1 = D5; //0;
int Sin2 = D6; //13;
int Sin3 = D7; //15;
int Sin4 = D8; //12;
int dutyCycle = 0;
const int stepsPerRevolution = 200; // 1.8° per step
int currentStep = 0;
int targetStep = 0;
int steering = 0;

void setup() {
    pinMode(receiverPin, INPUT);
    //Serial.begin(115200);
    pinMode(Sin1, OUTPUT);
    pinMode(Sin2, OUTPUT);
    pinMode(Sin3, OUTPUT);
    pinMode(Sin4, OUTPUT);
    analogWriteRange(100);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(receiverPin), readPulse, CHANGE);
    Serial.println("Hast Set Up ish");
}

void loop() {
    Serial.print("PulseWidth               ");
    Serial.println(pulseWidth);
 //   Serial.println("us");
    
 
    steering = pulseWidth;
    int angleSteering = map(steering, 996, 1996, 0, 360);
    targetStep = map(angleSteering, 0, 360, 0, stepsPerRevolution);
    
    if (abs(targetStep - currentStep) < 5) {

    } else {
        if (targetStep > currentStep) {
        stepForward();
        currentStep++;
        } else if (targetStep < currentStep) {
        stepBackward();
        currentStep--;
        }
    delay(5); // Controls speed
    } 
}

void readPulse() {
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