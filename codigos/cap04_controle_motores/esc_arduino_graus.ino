#include <Servo.h>

Servo esc;
const int PIN_ESC = 9;

void setup() {
  esc.attach(PIN_ESC);

  // Armar o ESC (obrigatório)
  esc.write(0);
  delay(3000);
}

void loop() {
  // Acelera gradualmente
  for (int val = 0; val <= 180; val++) {
    esc.write(val);
    delay(20);
  }
}