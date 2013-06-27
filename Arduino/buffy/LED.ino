int oldLEDVal = 0;
int led_max = 4095; //WARNING, very high
int led_high = 2000;
int led_med_high = 1500;
int led_med = 1000;
int led_low = 500;
int led_off = 0;

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
}

