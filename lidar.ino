#define FRAME_HEADER 170

bool readLidarFrame() {
  if (Serial1.read() != FRAME_HEADER) return false;

  for (int i = 0; i < FRAME_LENGTH; i++) {
    while (!Serial1.available());
    lidar_frame[i] = Serial1.read();
  }

  if (lidar_frame[2] != 1 || lidar_frame[3] != 97) return false;

  int segment = ((lidar_frame[10]*256 + lidar_frame[11]) / 2250);
  int points = (lidar_frame[6] - 5) / 3;

  if (points > 30 || segment >= LIDAR_RESOLUTION / 5) return false;

  for (int p = 0; p < 5; p++) {
    int idx = segment * 5 + p;
    if (idx >= LIDAR_RESOLUTION) continue;

    int dist = (lidar_frame[13 + p * 18] * 256 + lidar_frame[14 + p * 18]) * 0.25;
    if (dist < 8000) {
      distances[idx] = dist;
      signals[idx] = lidar_frame[12 + p * 18];
    }
  }

  return true;
}