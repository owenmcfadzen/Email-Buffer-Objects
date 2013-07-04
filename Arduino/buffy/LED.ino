#define LED_MAX 4095
#define LED_HIGH 2000
#define LED_OFF 0

#define LED_STATE_READY 0
#define LED_STATE_PULSING 1

int led_state = LED_STATE_READY;


int led_animation_counter = 0;
int brightness = 0;

int fade_amount = 100;    // how many points to fade the LED by
unsigned long last_led_timout = 0;

void led_setup() {
  Tlc.init();
}

void led_loop() {

  if (led_state == LED_STATE_PULSING) {
    // we're going UP
    
    led_animation_counter++;
    
    for (int i = 0; i <= 8; i++) {
      Tlc.set(i, brightness);
    }
  }

  Tlc.update();
}

void led_pulse_to(int n) {
  led_animation_counter = 0;
  led_state = LED_STATE_PULSING;
}

void slow_fade() {
  if (millis() - last_led_timout > 50) {
    // change the brightness for next time through the loop
    brightness += fade_amount;

    // reverse the direction of the fading at the ends of the fade
    if (brightness <= 0 || brightness >= (LED_HIGH - fade_amount)) {
      fade_amount = -fade_amount ; 
    } 

    last_led_timout = millis();
  }

  for (int i = 0; i <= 8; i++) {
    Tlc.set(i, brightness);
  }
}


