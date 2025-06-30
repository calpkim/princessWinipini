// /workspaces/princessWinipini/ESP 1 (Sender)/ReadPotNSend.ino
// princessWinipini Boat Project
// Created by calpkim & TitoSpike
// ©2025

//Chat GPT
#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t receiverMAC[] = {48:3F:DA:5E:6E:A2};  // replace with actual MAC

typedef struct struct_message {
  int potValue;
} struct_message;

struct_message dataToSend;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // ESP-NOW requires station mode
  WiFi.disconnect();    // ensure no connection to router
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
}

void loop() {
  int potVal = analogRead(A0);  // 0–1023
  dataToSend.potValue = potVal;

  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_send(, (uint8_t *) &dataToSend, sizeof(dataToSend));
  delay(200);  // send every 200ms
}