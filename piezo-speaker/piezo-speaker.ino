int doBeap = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    doBeap = Serial.parseInt();
  }

  if (doBeap == 1) {
    tone(7, 5000, 500);
  } else {
    noTone(7);
  }

  delay(10000);
}
