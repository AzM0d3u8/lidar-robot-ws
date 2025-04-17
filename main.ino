#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include <WebSocketClient.h>

#define LIDAR_RESOLUTION 80
#define FRAME_LENGTH 120
#define DIR_OUT1 6
#define DIR_OUT2 7

char ssid[] = "TP-LINK_B71D9D";
char pass[] = "87057850";
char serverAddress[] = "192.168.0.107";
int port = 8084;

WiFiClient wifi;
WebSocketClient client(wifi, serverAddress, port);

int lidar_frame[FRAME_LENGTH];
int distances[LIDAR_RESOLUTION];
int signals[LIDAR_RESOLUTION];

long lastSend = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(230400);

  pinMode(DIR_OUT1, OUTPUT);
  pinMode(DIR_OUT2, OUTPUT);

  for (int i = 0; i < LIDAR_RESOLUTION; i++) {
    distances[i] = 0;
    signals[i] = 50;
  }

  connectToWiFi(ssid, pass);

  Serial.println("Starting WebSocket...");
  client.begin();
}

void loop() {
  if (client.connected()) {
    if (readLidarFrame()) {
      if (millis() - lastSend > 50) {
        sendLidarData();
        lastSend = millis();
      }
    }
    receiveDirectionCommand();
  } else {
    Serial.println("WebSocket disconnected, reconnecting...");
    delay(1000);
    client.begin();
  }
}