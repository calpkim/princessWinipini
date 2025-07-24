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

uint8_t receiverMAC[] = {0x48, 0x3F, 0xDA, 0x57, 0x55, 0x5B};

typedef struct struct_message {
  int potValue1;
  int potValue2;
} struct_message;

struct_message dataToSend;

const int throttleGND = D1;  // Used to ground throttle pot
const int steeringGND = D2;  // Used to ground steering pot
const int steeringVCC = D3; // Used to provide VCC to steering pot
const int throttleVCC = D0; // Used to provide VCC to throttle pot

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // ESP-NOW requires station mode
  WiFi.disconnect();    // ensure no connection to router

  pinMode(throttleGND, INPUT);
  pinMode(steeringGND, INPUT);
  pinMode(steeringVCC, INPUT);
  pinMode(throttleVCC, INPUT);

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
  // TURN OFF STEERING
  pinMode(steeringGND, INPUT);   // Make sure steering is disconnected
  pinMode(steeringVCC, INPUT);  // Ensure steering VCC is off
  // TURN ON THROTTLE
  pinMode(throttleGND, OUTPUT);  // Set throttle GND to output
  pinMode(throttleVCC, OUTPUT);  // Turn on throttle VCC
  digitalWrite(throttleGND, LOW);    // Ground throttle
  digitalWrite(throttleVCC, HIGH);   // Turn on Power for throttle
  delay(50);                         // Wait for voltage to stabilize
  // READ THROTTLE
  dataToSend.potValue1 = analogRead(A0);
  //TURN OFF THROTTLE
  pinMode(throttleVCC, INPUT);  // Turn off throttle VCC
  pinMode(throttleVCC, INPUT);  // Turn off throttle VCC

  // === Read Steering ===
  // TURN OFF THROTTLE
  pinMode(throttleGND, INPUT);   // Make sure throttle is disconnected
  pinMode(throttleVCC, INPUT);  // Ensure throttle VCC is off
  // TURN ON STEERING
  pinMode(steeringGND, OUTPUT);  // Set steering GND to output
  pinMode(steeringVCC, OUTPUT);  // Turn on steering VCC
  digitalWrite(steeringGND, LOW);    // Ground steering
  digitalWrite(steeringVCC, HIGH);   // Turn on Power for steering
  delay(50);                         // Wait for voltage to stabilize
  // READ STEERING
  dataToSend.potValue2 = analogRead(A0);
  //TURN OFF STEERING
  pinMode(steeringGND, INPUT);   // Make sure steering is disconnected
  pinMode(steeringVCC, INPUT);  // Ensure steering VCC is off

    // === Print Data ===
  Serial.print("potValue1 = ");
  Serial.print(dataToSend.potValue1);
  Serial.print(" | potValue2 = ");
  Serial.println(dataToSend.potValue2);

  // === Send Data ===
  esp_now_send(receiverMAC, (uint8_t *) &dataToSend, sizeof(dataToSend));

  delay(200);
}
