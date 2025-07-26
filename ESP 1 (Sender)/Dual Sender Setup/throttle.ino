// /workspaces/princessWinipini/ESP 2 (Reciever)/Dual Sender Setup/throttle.ino
// princessWinipini Boat Project
// Created by calpkim & TitoSpike
// ©2025

#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t receiverMAC[] = {0x48, 0x3F, 0xDA, 0x57, 0x55, 0x5B};
typedef struct struct_message {
    char type;
    int throttle;
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
  
  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0); 

}

void loop(){
    dataToSend.throttle = analogRead(A0); // Read throttle value
    dataToSend.type = 'T'; // Type for Throttle


    Serial.print("Throttle Value: ");
    Serial.println(dataToSend.throttle);

    esp_now_send(receiverMAC, (uint8_t *) &dataToSend, sizeof(dataToSend));
}