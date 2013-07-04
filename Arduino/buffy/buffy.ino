#define DEVICE_ID 'A' // UNIQUE DEVICE ID
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
int current_mailbox = 0;
int removed_from_mailbox = 0;

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
    current_mailbox = 0;
    led_pulse_to(current_mailbox);
  }
  else if (serial_value == '1') {
    current_mailbox = 1;
    led_pulse_to(current_mailbox);
  }
  else if (serial_value == '2') {
    current_mailbox = 2 - removed_from_mailbox;
    led_pulse_to(current_mailbox);
  }
  else if (serial_value == '3') {
    current_mailbox = 3 - removed_from_mailbox;
    led_pulse_to(current_mailbox);
  }
  else if (serial_value == '4') {
    current_mailbox = 4 - removed_from_mailbox;
    led_pulse_to(current_mailbox);
  }
  else if (serial_value == '5') {
    current_mailbox = 5 - removed_from_mailbox;
    led_pulse_to(current_mailbox);
  }
  else if (serial_value == '6') {
    current_mailbox = 6 - removed_from_mailbox;
    led_pulse_to(current_mailbox);
  }
  else if (serial_value == '7') {
    current_mailbox = 7 - removed_from_mailbox;
    led_pulse_to(current_mailbox);
  }
  else if (serial_value == '8') {
    current_mailbox = 8 - removed_from_mailbox;
    led_pulse_to(current_mailbox);
  }
  else if (serial_value == '9') {
    current_mailbox = 9 - removed_from_mailbox;
    led_pulse_to(current_mailbox);
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

  // Reduce the mailbox by 1
  if (current_mailbox > 0) {
    current_mailbox--;
    removed_from_mailbox++;
    
    motor_tap();
    led_pulse_to(current_mailbox);
  }
  else {
    // Just pulse
    led_low_pulse_to(0);
  }
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
  
  // Reduce the mailbox by 1
  if (current_mailbox > 0) {
    removed_from_mailbox += current_mailbox;
    current_mailbox = 0;    
    
    motor_tap();
    led_pulse_to(current_mailbox);
  }
}

void neighbor_connect_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Attached to neighbor");

  led_low_pulse_to(current_mailbox);
}

void neighbor_detach_event() {
  Serial.print("DEVICE '");
  Serial.print(DEVICE_ID);
  Serial.println("': Detached from neighbor");

  led_low_pulse_to(0);
}












