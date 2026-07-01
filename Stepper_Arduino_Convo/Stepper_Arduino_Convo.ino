// Read PWM signals from FS-iA6B using Arduino Uno
#include <espnow.h>
const int receiverPin = D2;
volatile unsigned long pulseStart = 0;
volatile unsigned long pulseWidth = 0;

void setup() {
    pinMode(receiverPin, INPUT);
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(receiverPin), readPulse, CHANGE);
}

void loop() {
    Serial.print("PulseWidth");
    Serial.print(pulseWidth);
    Serial.println("us");
    delay(100);
}

ICACHE_RAM_ATTR void readPulse() {
    if (digitalRead(receiverPin)==HIGH) {
        pulseStart = micros();
    } else{
        pulseWidth = micros() - pulseStart;
    }
}