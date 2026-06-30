// Read PWM signals from FS-iA6B using Arduino Uno
const int receiverPin = 2;
volatile unsigned long pulseStart = 0;
volatile unsigned long pulseWidth = 0;

void setup() {
    pinMode(receiverPin, INPUT);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(receiverPin), readPulse, CHANGE);
}

void loop() {
    Serial.print("PulseWidth               ");
    Serial.println(pulseWidth);
 //   Serial.println("us");
    delay(100);
}

void readPulse() {
    if (digitalRead(receiverPin)==HIGH) {
        pulseStart = micros();
    } else{
        pulseWidth = micros() - pulseStart;
    }
}