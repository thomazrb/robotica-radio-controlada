#include <ESP32Servo.h>

Servo esc;
const int PIN_ESC = 13;

const int PULSO_MIN = 1000;
const int PULSO_MAX = 2000;

void setup() {
  esc.attach(PIN_ESC, PULSO_MIN, PULSO_MAX);

  // Armar o ESC
  esc.writeMicroseconds(PULSO_MIN);
  delay(3000);
}

void loop() {
  for (int pulso = PULSO_MIN; pulso <= PULSO_MAX; pulso += 10) {
    esc.writeMicroseconds(pulso);
    delay(10);
  }
}