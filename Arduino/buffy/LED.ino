int oldLEDVal = 0;
int led_max = 4095; //WARNING, very high
int led_high = 2000;
int led_med_high = 1500;
int led_med = 1000;
int led_low = 500;
int led_off = 0;

<<<<<<< HEAD
void set_multiple_leds(int n){
  Serial.print("turn on ");
  Serial.print(n);
  Serial.println(" lights");
  
  n = constrain(n, 0, 8);
  digitalWrite(LED_LATCH_PIN, LOW);
  shiftOut(LED_DATA_PIN, LED_CLOCK_PIN, MSBFIRST, led_sequence[n]);
  digitalWrite(LED_LATCH_PIN, HIGH);
=======
void setLed(int n){
  
  n = constrain(n, 0, 15);
  int time = millis();
  int d = 0;
  
  if(oldLEDVal > n){
    //Fade out
    for(int i = oldLEDVal; i > n; i--){
      tlc_addFade(i, led_high, led_off, time+d, time+200+d);
      d += 80; 
    }
  }
  else if(oldLEDVal < n) {
    d = 0;
    for (int i = oldLEDVal; i < n; i++){
      //Fade in
      tlc_addFade(i, led_off, led_high, time+d, time+200+d);
      d += 80;
    }
  }
  oldLEDVal = n;
>>>>>>> c163f1b17c6448722bdcfc82a11472e133446aa2
}

