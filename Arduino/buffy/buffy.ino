#define DEVICE_ID 'A'

#define LED_DRIVER 3
#define PUSH_BUTTON_PIN 5
#define REED_SENSOR_PIN 6
#define MOTOR_PIN 7
#define LED_DRIVER 9
#define LED_DRIVER 10
#define LED_DRIVER 11
#define LED_DRIVER 13

// LED Libraries
#include "Tlc5940.h";

void setup(){
  Serial.begin(9600);

  // Initialise the sensors (push button & reed)
  sensor_init();

  // Initialise the solenoid
  motor_init();

  // Initialise the LED Library
  led_init();
}

void loop(){
  update_led();
  update_sensor();
}

// Events
void serial_event(byte serial_value) {

  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("' received a command via XBee");

  if (serial_value == 'K') {
    // Listen for specific char
    motor_tap();
  }
  else {
    // Assume that serial_value is an int and turn on LEDs
    //    setLed(serial_value);
    //    set_lukes_led_test(serial_value);
  }
}

void rest_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Resting");
}

void short_press_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Short Press");
  motor_tap();
}

void long_press_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Long Press");
}

void neighbor_connect_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Attached to neighbor");
}

void neighbor_detach_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Detached from neighbor");
}





