#define LED_MAX 4095
#define LED_HIGH 2000
#define LED_OFF 0

int brightness = 0;    // how bright the LED is
int fadeAmount = 100;    // how many points to fade the LED by
unsigned long last_led_timout = 0;

void led_init() {
  Tlc.init();
}

void update_led() {

  if (millis() - last_led_timout > 90) {
    // change the brightness for next time through the loop
    brightness += fadeAmount;

    // reverse the direction of the fading at the ends of the fade
    if (brightness <= 0 || brightness >= (LED_HIGH - fadeAmount)) {
      fadeAmount = -fadeAmount ; 
    } 

    last_led_timout = millis();
  }

  for (int i = 0; i <= 8; i++) {
    Tlc.set(i, brightness);
  }
  
  Tlc.update();
}
