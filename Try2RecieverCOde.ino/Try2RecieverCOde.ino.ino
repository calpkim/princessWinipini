// /workspaces/princessWinipini/ESP 2 (Reciever)/RECIEVER CODE.ino
// princessWinipini Boat Project
// Created by calpkim & TitoSpike
// ©2025

// Import Libraries
#include <ESP8266WiFi.h>
#include <espnow.h>

// Steering
int Sin1 = D5; //0;
int Sin2 = D6; //13;
int Sin3 = D7; //15;
int Sin4 = D8; //12;

// Setting minimum duty cycle
int dutyCycle = 0;

const int stepsPerRevolution = 200; // 1.8° per step
int currentStep = 0;
int targetStep = 0;

typedef struct struct_message {
  char type;
  int value;
} struct_message;

struct_message incomingData;

int steering = 0;

void OnDataRecv(uint8_t *mac, uint8_t *incomingDataBytes, uint8_t len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));


  if (incomingData.type == 'S') {
    steering = incomingData.value;
  } else {
    Serial.println("Reception Error");
  }
  
  //Serial.print("Received Throttle: ");
  //Serial.print(throttle);
  //Serial.print(" | Steering: ");
  //Serial.println(steering);
  

  
}


void setup() {
  Serial.begin(115200);
  pinMode(Sin1, OUTPUT);
  pinMode(Sin2, OUTPUT);
  pinMode(Sin3, OUTPUT);
  pinMode(Sin4, OUTPUT);
  analogWriteRange(100);
  Serial.println("Hast Set Up ish");
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  int angleSteering = map(steering, 0, 1023, 0, 360);
  targetStep = map(angleSteering, 0, 360, 0, stepsPerRevolution);
  Serial.println(targetStep);
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