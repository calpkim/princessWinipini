// /workspaces/princessWinipini/ESP 2 (Reciever)/RecieveValNMove.ino
// princessWinipini Boat Project
// Created by calpkim & TitoSpike
// ©2025

#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct struct_message {
  int potValue;
} struct_message;

struct_message incomingData;

// Motor pins
const int ENA = D7;
const int IN1 = D1;
const int IN2 = D2;

void OnDataRecv(uint8_t *mac, uint8_t *incomingDataBytes, uint8_t len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));
  int speed = map(incomingData.potValue, 0, 1023, 0, 100);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
}

void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
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