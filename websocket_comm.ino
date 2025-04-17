void sendLidarData() {
  String payload = "";
  for (int i = 0; i < LIDAR_RESOLUTION; i++) {
    payload.concat(distances[i]);
    payload.concat(",");
    payload.concat(signals[i]);
    payload.concat(",");
  }
  client.beginMessage(TYPE_TEXT);
  client.print(payload);
  client.endMessage();
}

void receiveDirectionCommand() {
  int msgSize = client.parseMessage();
  if (msgSize > 0) {
    String command = client.readString();
    Serial.print("Direction: ");
    Serial.println(command);
    controlMovement(command);
  }
}