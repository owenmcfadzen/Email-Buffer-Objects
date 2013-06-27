#define DEVICE_ID 'A'
#define FORCE_SENSOR_PIN A0 
#define LED_DATA_PIN 2
#define LED_LATCH_PIN 3
#define LED_CLOCK_PIN 4

#define SERIAL_STATE_READY 1
#define SERIAL_STATE_READING 2

unsigned long last_led_time = 0;
int serial_state = SERIAL_STATE_READY;
byte aValue = 0;
boolean getTheNextByte = false;
boolean newValue = false;

void setup(){
  Serial.begin(9600);
  pinMode(LED_DATA_PIN, OUTPUT);
  pinMode(LED_LATCH_PIN, OUTPUT);
  pinMode(LED_CLOCK_PIN, OUTPUT);
}

void loop(){
  updateSensor();
  if(newValue){
    setNewLed(aValue);
    newValue = false;
  }
}

void serialEvent() {
  while(Serial.available()) {
    byte inByte = Serial.read();
    if(getTheNextByte){
      aValue = inByte;
      newValue = true;
      getTheNextByte = false;
    }

    if(inByte == DEVICE_ID){
      getTheNextByte = true;
    }
  } 
}

/*Events*/
void liftEvent(){
  Serial.println("Lifted");
}
void restEvent(){
  Serial.println("Resting");
}
void shortPressEvent(){
  Serial.println("Short Press");
}
void longPressEvent(){
  Serial.println("Long Press");
}






