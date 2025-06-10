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
