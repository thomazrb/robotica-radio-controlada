// Pinos de controle
const int IN1 = 5;
const int IN2 = 6;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  // Frente a 50% de força
  analogWrite(IN1, 128); // PWM em IN1
  digitalWrite(IN2, LOW);
  delay(2000);

  // Ré a 100% de força
  digitalWrite(IN1, LOW);
  analogWrite(IN2, 255); // PWM em IN2
  delay(2000);
}