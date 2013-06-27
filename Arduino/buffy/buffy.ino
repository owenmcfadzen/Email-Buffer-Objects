#define DEVICE_ID 'B'
#define FORCE_SENSOR_PIN A0 
#define LED_DATA_PIN 2
#define LED_LATCH_PIN 3
#define LED_CLOCK_PIN 4

void setup(){
  Serial.begin(9600);
  pinMode(LED_DATA_PIN, OUTPUT);
  pinMode(LED_LATCH_PIN, OUTPUT);
  pinMode(LED_CLOCK_PIN, OUTPUT);
}

void loop(){
  update_sensor();
}

/* Events */
void serial_event(byte serial_value) {
  /* Assume that serial_value is an int and turn on LEDs */
  set_multiple_leds(serial_value);
}

void lift_event() {
  Serial.println("Lifted");
}

void rest_event() {
  Serial.println("Resting");
}

void short_press_event() {
  Serial.println("Short Press");
}
 
void long_press_event() {
  Serial.println("Long Press");
}






