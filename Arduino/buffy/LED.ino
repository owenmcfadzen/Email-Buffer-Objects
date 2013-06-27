int led_sequence[9] = {
  B00000000,
  B10000000,
  B11000000,
  B11100000,
  B11110000,
  B11111000,
  B11111100,
  B11111110,
  B11111111}; 
 

void setNewLed(int n){
  n = constrain(n, 0, 7);
  digitalWrite(LED_LATCH_PIN, LOW);
  shiftOut(LED_DATA_PIN, LED_CLOCK_PIN, MSBFIRST, led_sequence[n]);
  digitalWrite(LED_LATCH_PIN, HIGH);
}
