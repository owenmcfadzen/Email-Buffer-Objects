#define LED_MAX 4095
#define LED_HIGH 1000
#define LED_OFF 0

int led_old_val = 0;

void set_lukes_led_test(int n) {
  
  Tlc.clear();
  
  // split the light intensity
  int led_level = 4095 / 4;
  
  // how many whole leds to light up
  int whole_leds = floor(n / 4);
  
  // what's left is used to light the last led
  int last_led_level = n % 4;
  
  
  for (int i = 0; i <= whole_leds; i++) {
    Tlc.set(i, led_level * 4);
  }
  
  if (last_led_level > 0) {
    Tlc.set(whole_leds + 1, led_level * last_led_level);
  }
  
}


void setLed(int led_new_val){
  /* Accept a number: 0 = no leds, 1-8 = leds */
  led_new_val = constrain(led_new_val, 0, 8);
  
  Serial.print("turning on ");
  Serial.print(led_new_val);
  Serial.println(" LEDs");
  
  int time = millis();
  int led_delay = 0;
  
  if(led_old_val > led_new_val){
    //Fade out
    for(int i = led_old_val; i > led_new_val; i--){
      tlc_addFade(i, LED_HIGH, LED_OFF, time + led_delay, time + led_delay + 200);
      led_delay += 80; 
    }
  }
  else if(led_old_val < led_new_val) {
    led_delay = 0;
    for (int i = led_old_val; i <= led_new_val; i++){
      //Fade in
      tlc_addFade(i, LED_OFF, LED_HIGH, time + led_delay, time + led_delay + 200);
      led_delay += 80;
    }
  }
  
  /* Remember the current value for next time */
  led_old_val = led_new_val;
}

