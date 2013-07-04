void motor_setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);
}

void motor_tap() {
  digitalWrite(MOTOR_PIN, HIGH);
  delay(100);
  digitalWrite(MOTOR_PIN, LOW);
}
