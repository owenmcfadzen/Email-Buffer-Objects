void motor_init() {
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, HIGH);
}

void motor_tap() {
  digitalWrite(MOTOR_PIN, HIGH);
  delay(300);
  digitalWrite(MOTOR_PIN, LOW);
}
