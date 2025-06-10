#include <WiFi.h>

// Állítsd be a Wi-Fi adatokat
const char* ssid     = "Kifli";
const char* password = "kurva111";

// Node-RED szerver IP és port
const char* host = "192.168.1.120";  // Node-RED géped IP-je
const uint16_t port = 5000;          // TCP port, amit a Node-RED figyel

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.print("WiFi kapcsolódás...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" kapcsolódva!");

  Serial.printf("Kapcsolódás a szerverhez: %s:%d\n", host, port);
  if (client.connect(host, port)) {
    Serial.println("Kapcsolódás sikeres!");
    client.println("Hello Node-RED!");
  } else {
    Serial.println("Sikertelen kapcsolat.");
  }
}

void loop() {
  // Példa: 5 másodpercenként küldj adatot
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    if (client.connected()) {
      client.println("ESP32 --> Node-RED: szia!");
      Serial.println("Üzenet küldve.");
    } else {
      Serial.println("Kapcsolat megszakadt, újracsatlakozás...");
      if (client.connect(host, port)) {
        Serial.println("Újracsatlakozás sikeres.");
      }
    }
    lastSend = millis();

    if (!client.connect(host, port)) {
  Serial.println("Sikertelen kapcsolat.");
  Serial.print("WiFi állapot: ");
  Serial.println(WiFi.status());
  Serial.print("Host: ");
  Serial.println(host);
  Serial.print("Port: ");
  Serial.println(port);
}

  }

  // Olvasd a szervertől kapott adatot
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.print("Node-RED válasz: ");
    Serial.println(line);
  }
}
