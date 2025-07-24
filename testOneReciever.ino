// /workspaces/princessWinipini/ESP 2 (Reciever)/mix.ino
// princessWinipini Boat Project
// Created by calpkim & TitoSpike
// ©2025

//A work in advanced, this is GOING TO FAIL : )

// Import Libraries
#include <ESP8266WiFi.h>
#include <espnow.h>

// Motor A
int ENA1 = D0; // 16;
int IN1 = D1; // 5;
int IN2 = D2; // 4;

// Motor B
int IN3 = D3; //0;
int IN4 = D7; //13;
int ENA2 = D8; //15;

// Setting minimum duty cycle
int dutyCycle = 0;


// 
typedef struct struct_message {
  int potValue1; // Motor B, throttle
  int potValue2; // Motor A, steering
} struct_message;

struct_message incomingData;

void OnDataRecv(uint8_t *mac, uint8_t *incomingDataBytes, uint8_t len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));
  int potValue1 = incomingData.potValue1;
  int potValue2 = incomingData.potValue2;

  int speedThrottle = 0;
  int speedSteering = 0;

  if (potValue1 <= 307) {
    // REVERSE: Scale 0–307 to 0–30
    speedThrottle = map(potValue1, 0, 307, 0, 30);
    // Motor B Reverse
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA2, speedThrottle);
    

  } else if (potValue1 >= 308) {
    // FORWARD: Scale 308–1023 to 0–100
    speedThrottle = map(potValue1, 308, 1023, 0, 100);
    // Motor B Forward
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA2, speedThrottle);


  } else {
    // STOP
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA2, dutyCycle);
  }
//
//
//
//
//
  /*if (potValue2 <= 512) {
    // LEFT: Scale 0–512 to 0–100
    speedSteering = map(potValue2, 0, 512, 0, 100);
    // Motor A Left
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA1, speedSteering);


  } else if (potValue2 >= 513) {
    // RIGHT: Scale 513–1023 to 0–100
    speedSteering = map(potValue2, 513, 1023, 0, 100);
    // Motor A Right
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA1, speedSteering);
  } else {
    // STOP
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA1, dutyCycle);
  }
  */
}


void setup() {
  Serial.begin(115200);
  pinMode(ENA2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  analogWriteRange(100);

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
  // Do nothing; data received via callback
}