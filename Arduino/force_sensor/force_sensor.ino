#define FORCE_STATE_RESTING 1
#define FORCE_STATE_LIFTING 2
#define FORCE_STATE_PRESSING 3
#define FORCE_STATE_LONG_PRESS 4

/* Define the pins */
int force_sensor = A0;

int force_value = 0;
int force_state = 0;
unsigned long force_press_start = 0;
unsigned long time = 0;

/* Define the force thresholds to measure interactions */
int force_on_rest = 279;
int force_on_lift = 250;
int force_on_press = 290;
int long_press_time = 1000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  force_value = analogRead(force_sensor);
  //Serial.println(force_value);

  /* measure the forces */
  if (force_value < force_on_rest + 5 
  && force_value > force_on_rest - 5
  && force_state != FORCE_STATE_RESTING) {
    if (force_state == FORCE_STATE_PRESSING) {
      // this must be a short press
      Serial.println("short press");
    }
    // the block is resting
    Serial.println("resting");
    force_state = FORCE_STATE_RESTING;
  }
  else if (force_value <= force_on_lift 
  && force_state != FORCE_STATE_LIFTING) {
    // the block is lifted
    Serial.println("lifted");
    force_state = FORCE_STATE_LIFTING;
  }
  else if (force_value >= force_on_press 
  && force_state != FORCE_STATE_PRESSING
  && force_state != FORCE_STATE_LONG_PRESS) {
    // the block is press
    force_state = FORCE_STATE_PRESSING;
    force_press_start = millis();
  }
  
  if (force_state == FORCE_STATE_PRESSING) {
    time = millis();
    if (time - force_press_start > long_press_time) {
      Serial.println("long press");
      force_state = FORCE_STATE_LONG_PRESS;
    }
  }
  
  delay(50);
}
