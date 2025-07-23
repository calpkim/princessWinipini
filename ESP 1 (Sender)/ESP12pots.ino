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

const int throttleGND = D1;  // Used to ground throttle pot
const int steeringGND = D2;  // Used to ground steering pot

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // ESP-NOW requires station mode
  WiFi.disconnect();    // ensure no connection to router

  pinMode(throttleGND, OUTPUT);
  pinMode(steeringGND, OUTPUT);


  digitalWrite(throttleGND, HIGH); // Start off not grounded
  digitalWrite(steeringGND, HIGH); // Start off not grounded

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }
// D0 is throttle positive (3v) and D1 is throttle negative (GND)
// D3 is steering positive (3v) and D2 is steering negative (GND)
//A0 is the analog input for both, have to on and off each port accordingly and read at the same time in order to read both simultaniously

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  
  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0); 
}

void loop() {
  // === Read Throttle ===
  digitalWrite(steeringGND, HIGH);   // Make sure steering is disconnected
  digitalWrite(throttleGND, LOW);    // Ground throttle
  delay(10);                         // Wait for voltage to stabilize
  dataToSend.potValue1 = analogRead(A0);
  digitalWrite(throttleGND, HIGH);   // Disconnect again

  // === Read Steering ===
  digitalWrite(throttleGND, HIGH);   // Ensure throttle is disconnected
  digitalWrite(steeringGND, LOW);    // Ground steering
  delay(10);                         // Wait for voltage to stabilize
  dataToSend.potValue2 = analogRead(A0);
  digitalWrite(steeringGND, HIGH);   // Disconnect again

  // === Send Data ===
  esp_now_send(receiverMAC, (uint8_t *) &dataToSend, sizeof(dataToSend));

  delay(200);
}
