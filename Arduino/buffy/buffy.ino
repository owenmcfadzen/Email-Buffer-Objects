#define DEVICE_ID 'A'
#define FORCE_SENSOR_PIN A0 

/*LED Libraries*/
#include "Tlc5940.h"
#include "tlc_fades.h"
TLC_CHANNEL_TYPE channel;


void setup(){
  Serial.begin(9600);
  /*LED Library*/
  Tlc.init();
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






