unsigned long current_time = 0;
unsigned long last_time = 0;
int led_counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  current_time = millis();
  
  if (current_time - last_time > 2000) {
    
    /* Broadcast a message */
    Serial.write('A');
    Serial.write(led_counter);
//    Serial.println(led_counter);
    
    led_counter++;
    if (led_counter > 8) {
      led_counter = 0;
    }
    
    last_time = current_time;
  }
  
}
