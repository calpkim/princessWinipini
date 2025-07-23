#include <ESP8266WiFi.h>
#include <espnow.h>

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  Serial.print("Received: ");
  for (int i = 0; i < len; i++) {
    Serial.print((char)incomingData[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();  // Disconnect from any AP
  
  // Set a fixed channel for ESP-NOW (e.g., channel 1)
  wifi_promiscuous_enable(1);  // Required to set channel manually
  wifi_set_channel(1);         // <-- Set your chosen channel
  wifi_promiscuous_enable(0);

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}
void loop() {}
