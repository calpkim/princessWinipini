// /workspaces/princessWinipini/tests/Connection Tests/Test Send.ino
// princessWinipini Boat Project
// Created by calpkim & TitoSpike
// ©2025


#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t receiverMAC[] = {0x48, 0x3F, 0xDA, 0x57, 0x55, 0x5B};

const char test[] = "test";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();  // Prevent connection to routers

  // Set the same channel as the receiver (e.g., channel 1)
  wifi_promiscuous_enable(1);
  wifi_set_channel(1);
  wifi_promiscuous_enable(0);

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);  // 1 = channel

  uint8_t result = esp_now_send(receiverMAC, (uint8_t *)test, sizeof(test));
  if (result == 0) {
    Serial.println("Message sent successfully");
  } else {
    Serial.print("Send failed: ");
    Serial.println(result);
  }
}

void loop() {}
