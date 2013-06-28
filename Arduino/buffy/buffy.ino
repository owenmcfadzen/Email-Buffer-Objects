#define DEVICE_ID 'A'
#define FORCE_SENSOR_PIN A0
#define LED_DATA_PIN 2
#define LED_LATCH_PIN 3
#define LED_CLOCK_PIN 4
#define MOTOR_PIN 7

/*LED Libraries*/
#include "Tlc5940.h"
#include "tlc_fades.h"

void setup(){
  Serial.begin(9600);

  /* Initialise the solenoid pins */
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);

  /* LED Library */
  Tlc.init();
}

void loop(){
  update_sensor();
  tlc_updateFades(millis());
}

/* Events */
void serial_event(byte serial_value) {
  if (serial_value == 'K') {
    /* Listen for specific char */
    digitalWrite(MOTOR_PIN, HIGH);
    delay(100);
    digitalWrite(MOTOR_PIN, LOW);
  }
  else {
    /* Assume that serial_value is an int and turn on LEDs */
    setLed(serial_value);
  }
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

