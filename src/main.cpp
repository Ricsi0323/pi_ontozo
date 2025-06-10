<<<<<<< HEAD
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
=======
#include <Arduino.h>
#include <WiFi.h>

// WiFi beállítások
const char* ssid = "***************";
const char* password = "**************";

#define rele 14
#define status_led 19
#define kliens 21

// TCP szerver a 8888-as porton
WiFiServer server(8888);

void setup_wifi();

void setup() {
  Serial.begin(115200);
  setup_wifi();
  server.begin(); // TCP szerver indítása
  Serial.println("TCP Server started on port 8888");
  pinMode(rele, OUTPUT);
  pinMode(kliens, OUTPUT);
  pinMode(status_led, OUTPUT);
// alapállapot
  digitalWrite(rele, LOW); // alapállapot
  digitalWrite(kliens, LOW); // alapállapot
}

void loop() {
  WiFiClient client = server.available(); // Új kliens ellenőrzése

  if (client) {
    digitalWrite(kliens,HIGH);
    Serial.println("New client connected");

    while (client.connected()) {
      if (client.available()) {
        String message = client.readStringUntil('\n');
        message.trim();  // eltávolítja a \r vagy \n karaktereket
        Serial.print("Received from client: ");
        Serial.println(message);

        // Kapott üzenet alapján vezéreljük a GPIO-t
        if (message == "1") {
          digitalWrite(rele, HIGH);
          Serial.println("Relay ON");
        } else if (message == "0") {
          digitalWrite(rele, LOW);
          Serial.println("Relay OFF");
        }

        client.println("ESP32 received: " + message);
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi!");
  digitalWrite(status_led,HIGH);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
>>>>>>> c53d297b7f83418c9a698cd5163d847e7a7d45be
