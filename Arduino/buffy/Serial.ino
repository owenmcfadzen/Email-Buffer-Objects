/**
 * Handle the data coming from the Serial Buffer.
 * Check the data is for this device using DEVICE_ID
 **/

boolean serial_process_next_byte = false;

void serialEvent() {
  while(Serial.available()) {
    byte new_byte = Serial.read();

    if(serial_process_next_byte){
      serial_event(new_byte);
      serial_process_next_byte = false;
//      Serial.flush();
    }

    if(new_byte == DEVICE_ID){
      serial_process_next_byte = true;
    }
  } 
}


