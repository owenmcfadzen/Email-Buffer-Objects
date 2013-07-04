#define DEVICE_ID 'B' // UNIQUE DEVICE ID
#define TRIGGER_SOLENOID 'K' // TRIGGER SOLENOID COMMAND

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

// Store the mailbox total for this device
int mailbox_total = 0;

void setup(){
  Serial.begin(9600);

  // Initialise the sensors (push button & reed)
  sensor_setup();

  // Initialise the solenoid
  motor_setup();

  // Initialise the LED Library
  led_setup();
}

void loop(){
  led_loop();
  sensor_loop();
}

// Events
void serial_event(byte serial_value) {

  // Listen for specific char
  if (serial_value == TRIGGER_SOLENOID) {
    motor_tap();
  }
  else if (serial_value == '0') {
    led_pulse_to(0);
  }
  else if (serial_value == '1') {
    led_pulse_to(1);
  }
  else if (serial_value == '2') {
    led_pulse_to(2);
  }
  else if (serial_value == '3') {
    led_pulse_to(3);
  }
  else if (serial_value == '4') {
    led_pulse_to(4);
  }
  else if (serial_value == '5') {
    led_pulse_to(5);
  }
  else if (serial_value == '6') {
    led_pulse_to(6);
  }
  else if (serial_value == '7') {
    led_pulse_to(7);
  }
  else if (serial_value == '8') {
    led_pulse_to(8);
  }
  else if (serial_value == '9') {
    led_pulse_to(9);
  }  
  else {
    // For debugging unusual commands from server
    Serial.print("DEVICE '");
    Serial.print(DEVICE_ID);
    Serial.print("': Unknown command ");
    Serial.println(serial_value);
  }
}

void rest_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Resting");
}

void start_press_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Start Press");
  motor_tap();
}

void release_press_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Release Press");
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

  motor_tap();
}

void neighbor_detach_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Detached from neighbor");

  motor_tap();
}











