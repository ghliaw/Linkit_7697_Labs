#define RED_LED 2
#define POTENTIOMETER A0
void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  int value;

  value = analogRead(POTENTIOMETER);
  Serial.println(value);
  analogWrite(RED_LED, value/16);
}
