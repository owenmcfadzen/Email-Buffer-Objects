#define PB_STATE_READY 1
#define PB_STATE_PRESSING 2
#define PB_STATE_LONG_PRESS 3

#define REED_STATE_READY 1
#define REED_STATE_CONNECTED 2
#define REED_STATE_DISCONNECTING 3

int pb_state = PB_STATE_READY;
int pb_sensor_value = 0;
unsigned long pb_start_time = 0;

boolean reed_state = REED_STATE_READY;
boolean reed_sensor_value = false;
unsigned long reed_detach_time = 0;

void sensor_setup() {
  // we don't need to do anything
}

void sensor_loop() {
  pb_sensor_value = digitalRead(PUSH_BUTTON_PIN);

  if (pb_sensor_value == HIGH && pb_state == PB_STATE_READY) {
    // we are now pressing the button
    pb_state = PB_STATE_PRESSING;
    pb_start_time = millis();
    start_press_event();
  }
  else if (pb_sensor_value == LOW && pb_state != PB_STATE_READY) {
    // we have now released the button
    if (pb_state == PB_STATE_PRESSING) {
      release_press_event();
    }
    pb_state = PB_STATE_READY;
    rest_event();
  }

  // Count how long we've been pressing the button down
  if (pb_state == PB_STATE_PRESSING) {
    if (millis() - pb_start_time > 1000){
      // We must have pressed for a long time
      pb_state = PB_STATE_LONG_PRESS;
      long_press_event();
    }
  }

  // get reed sensor
  reed_sensor_value = digitalRead(REED_SENSOR_PIN);
  
  if (reed_sensor_value == HIGH && reed_state != REED_STATE_CONNECTED) {
    // We must be touching
    if (reed_state == REED_STATE_READY) {
      neighbor_connect_event();
    }
    reed_state = REED_STATE_CONNECTED;
  }
  else if (reed_sensor_value == LOW && reed_state == REED_STATE_CONNECTED) {
    // We must have disconnected
    reed_state = REED_STATE_DISCONNECTING;
    reed_detach_time = millis();
  }
  
  if (reed_state == REED_STATE_DISCONNECTING) {
    if (millis() - reed_detach_time > 2000) {
      // We must have detached for a long time
      reed_state = REED_STATE_READY;
      neighbor_detach_event();
    }
  }
}

