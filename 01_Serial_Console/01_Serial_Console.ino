void setup() {
  // opens serial port, set data rate to 9600 bps
  Serial.begin(9600); 
}

void loop() {
  static char buf[200];
  static int  length = 0;
  int incoming_byte; 

  // If there is any data incoming, read a byte and put it on string buffer
  if(Serial.available() > 0) {
    incoming_byte = Serial.read();  // read the incoming byte
    buf[length++] = incoming_byte;  // put the incoming byte to string buffer
    if(incoming_byte == '\n') { // if LF is incoming, send back the whole string with its length  
      buf[length] = '\0'; // put the end character 
      Serial.print("(");
      Serial.print(length);
      Serial.print(") ");
      Serial.print(buf);
      length = 0; // reset the length for receiving next string
    }
  }
}
