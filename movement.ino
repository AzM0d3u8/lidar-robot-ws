void controlMovement(String command) {
  if (command == "left") {
    digitalWrite(DIR_OUT1, HIGH);
    digitalWrite(DIR_OUT2, LOW);
  } else if (command == "right") {
    digitalWrite(DIR_OUT1, LOW);
    digitalWrite(DIR_OUT2, HIGH);
  } else if (command == "forward") {
    digitalWrite(DIR_OUT1, HIGH);
    digitalWrite(DIR_OUT2, HIGH);
  } else if (command == "stop") {
    digitalWrite(DIR_OUT1, LOW);
    digitalWrite(DIR_OUT2, LOW);
  }
}