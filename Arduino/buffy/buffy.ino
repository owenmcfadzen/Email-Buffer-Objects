#define DEVICE_ID 'A'
#define FORCE_SENSOR_PIN A0 
<<<<<<< HEAD
<<<<<<< HEAD
#define LED_DATA_PIN 2
#define LED_LATCH_PIN 3
#define LED_CLOCK_PIN 4
#define MOTOR_PIN 7

void setup(){
  Serial.begin(9600);
  
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);
  
  pinMode(LED_DATA_PIN, OUTPUT);
  pinMode(LED_LATCH_PIN, OUTPUT);
  pinMode(LED_CLOCK_PIN, OUTPUT);
=======

/*LED Libraries*/
#include "Tlc5940.h"
#include "tlc_fades.h"
TLC_CHANNEL_TYPE channel;


void setup(){
  Serial.begin(9600);
  /*LED Library*/
  Tlc.init();
>>>>>>> c163f1b17c6448722bdcfc82a11472e133446aa2
=======

/*LED Libraries*/
#include "Tlc5940.h"
#include "tlc_fades.h"
TLC_CHANNEL_TYPE channel;


void setup(){
  Serial.begin(9600);
  /*LED Library*/
  Tlc.init();
>>>>>>> c163f1b17c6448722bdcfc82a11472e133446aa2
}

void loop(){
  update_sensor();
  tlc_updateFades(millis());
}

/* Events */
void serial_event(byte serial_value) {
  /* Assume that serial_value is an int and turn on LEDs */
//  set_multiple_leds(serial_value);
  setLed(serial_value);
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






