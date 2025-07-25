// /workspaces/princessWinipini/ESP 1 (Sender)/OUTPUT_OPEN_DRAIN.ino
// princessWinipini Boat Project
// Created by calpkim & TitoSpike
// ©2025

#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t receiverMAC[] = {0x48, 0x3F, 0xDA, 0x57, 0x55, 0x5B};

typedef struct struct_message {
  int potValue1;
  int potValue2;
} struct_message;

struct_message dataToSend;

const int throttle = D2;  // Throttle pin
const int steering = D1;  // Steering pin

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // ESP-NOW requires station mode
  WiFi.disconnect();    // ensure no connection to router

  pinMode(throttle, INPUT); // Throttle 
  pinMode(steering, INPUT); // Steering 

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  
  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0); 
}

void loop() {
  // TURN OFF EVERYTHING
  pinMode(throttle, INPUT);   // Make sure throttle is disconnected
  pinMode(steering, INPUT);   // Make sure steering is disconnected

  // === Read Throttle ===
  pinMode(throttle, OUTPUT_OPEN_DRAIN);  // Set throttle to open drain mode
  digitalWrite(throttle, HIGH);
  delay(100);
  dataToSend.potValue1 = analogRead(A0); // Read throttle value
  pinMode(throttle, INPUT);  // Turn off throttle

  // === Read Steering ===
  pinMode(steering, OUTPUT_OPEN_DRAIN);  // Set steering to open drain mode
  digitalWrite(steering, HIGH);
  delay(100);
  dataToSend.potValue2 = analogRead(A0); // Read steering value
  pinMode(steering, INPUT);  // Turn off steering
  
  // === Print Data ===
  Serial.print("potValue1 = ");
  Serial.print(dataToSend.potValue1);
  Serial.print(" | potValue2 = ");
  Serial.println(dataToSend.potValue2);

  // === Send Data ===
  esp_now_send(receiverMAC, (uint8_t *) &dataToSend, sizeof(dataToSend));

  delay(200);
}
