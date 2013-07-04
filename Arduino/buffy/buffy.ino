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

  if (serial_value == TRIGGER_SOLENOID) {
    // Listen for specific char
    motor_tap();
  }
  else {
    // cast incoming byte to int
    // we expect this number to be between 0 - 254
    int new_mailbox_total = ((int) serial_value);

    if (new_mailbox_total != mailbox_total) {
      led_pulse_to(new_mailbox_total);
    }

    mailbox_total = new_mailbox_total;
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










