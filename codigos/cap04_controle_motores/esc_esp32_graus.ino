#include <ESP32Servo.h>

Servo esc;
const int PIN_ESC = 13;

void setup() {
  esc.attach(PIN_ESC);

  // Armar o ESC
  esc.write(0);
  delay(3000);
}

void loop() {
  for (int val = 0; val <= 180; val++) {
    esc.write(val);
    delay(20);
  }
}