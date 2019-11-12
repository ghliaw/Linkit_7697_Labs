#define LED_FLASH_INTERVAL  500 // ms
#define BUTTON_READ_INTERVAL 1000 // ms
#define RED_LED 2
#define GREEN_LED 3
#define BUTTON  5

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON, INPUT);    
}

void led_on(int turn)
{
  switch (turn) {
    case 0:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      break;
    case 1:
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      break;
    default:
      break;
  }
}

void led_off()
{
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

void loop() {
  static unsigned long last_time_led, last_time_button;
  static bool allow_read_button = true;
  static bool toggle_on = false;
  static int turn = 0; 
  int val;
  // read button input P5
  if(allow_read_button) {
    val = digitalRead(BUTTON);
    if (val==HIGH) {
      toggle_on = !toggle_on;
      if(toggle_on) {
        last_time_led = millis();
        led_on(turn);
        turn = (turn+1)%2;
        Serial.println("LED ON");
      }
      else {
        led_off();
        Serial.println("LED OFF");
      }
      allow_read_button = false;
      last_time_button = millis();
    }
  }
  else {
    if(millis()-last_time_button >= BUTTON_READ_INTERVAL)
      allow_read_button = true;
  }

  // light led
  if(toggle_on && millis()-last_time_led >= LED_FLASH_INTERVAL) {
    last_time_led = millis();
    led_on(turn);
    turn = (turn+1)%2;
  }
}
