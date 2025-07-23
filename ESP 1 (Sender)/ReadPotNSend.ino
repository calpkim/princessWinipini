// /workspaces/princessWinipini/ESP 1 (Sender)/ReadPotNSend.ino
// princessWinipini Boat Project
// Created by calpkim & TitoSpike
// ©2025

//Chat GPT
/*
    const int switchPin = 2; // Example digital pin

    void setup() {
      pinMode(switchPin, INPUT);
    }

    void loop() {
      int switchState = digitalRead(switchPin);
      if (switchState == LOW) {
        // Switch is closed (on)
        // Do something when switch is on
      } else {
        // Switch is open (off)
        // Do something when switch is off
      }
    }
*/
#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t receiverMAC[] = {0x48, 0x3F, 0xDA, 0x5E, 0x6E, 0xA2};

typedef struct struct_message {
  int potValue1;
  int potValue2;
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

void loop() {
  dataToSend.potValue1 = analogRead(A0); // Throttle pot on A0
  //dataToSend.potValue2 = analogRead(A1); // Steering pot on A1 (example pin)

  esp_now_send(receiverMAC, (uint8_t *) &dataToSend, sizeof(dataToSend));
  delay(200);  // send every 200ms
}
