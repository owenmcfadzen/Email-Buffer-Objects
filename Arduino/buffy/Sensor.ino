#define FORCE_STATE_RESTING 1
#define FORCE_STATE_LIFTING 2
#define FORCE_STATE_PRESSING 3
#define FORCE_STATE_LONG_PRESS 4

/* Define the force thresholds to measure interactions */
int force_on_rest = 250;
int force_on_lift = 0;
int force_on_press = 700;
int long_press_time = 1000;

int force_value = 0;
int force_state = 0;
unsigned long force_press_start = 0;

void updateSensor() {
  force_value = analogRead(FORCE_SENSOR_PIN);
  //Serial.println(force_value);
  if(force_value < force_on_rest + 50
    && force_value > force_on_rest - 50 
    && force_state != FORCE_STATE_RESTING){
    /*We must be resting */
    if(force_state == FORCE_STATE_PRESSING){ 
      shortPressEvent();
    }
    force_state = FORCE_STATE_RESTING;
    restEvent();
  }

  else if (force_value <= force_on_lift 
    && force_state != FORCE_STATE_LIFTING ){
    /*We must be lifted*/
    force_state = FORCE_STATE_LIFTING;
    liftEvent();
  }

  else if (force_value > force_on_press 
    && force_state != FORCE_STATE_PRESSING
    && force_state != FORCE_STATE_LONG_PRESS){
    /*We must be pressing*/
    force_state = FORCE_STATE_PRESSING;
    force_press_start = millis();
  }

  /*Count how long we have been pressing*/
  if (force_state == FORCE_STATE_PRESSING ){
    if (millis() - force_press_start > long_press_time){
      /*We must have pressed for a long time*/
      force_state = FORCE_STATE_LONG_PRESS;
      longPressEvent();
    }

  }
}


