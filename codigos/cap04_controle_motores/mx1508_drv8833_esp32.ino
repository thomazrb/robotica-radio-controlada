/ Pinos de controle
const int IN1 = 5;
const int IN2 = 18;

const int freq = 1000; // Frequência menor costuma funcionar bem nesses drivers
const int resolucao = 8;

void setup() {
  // PWM aplicado diretamente nos pinos de direção
  ledcAttach(IN1, freq, resolucao);
  ledcAttach(IN2, freq, resolucao);
}

void loop() {
  // Frente a 50% de força
  ledcWrite(IN1, 128); // PWM em IN1
  ledcWrite(IN2, 0);   // IN2 em LOW
  delay(2000);

  // Ré a 100% de força
  ledcWrite(IN1, 0);   // IN1 em LOW
  ledcWrite(IN2, 255); // PWM em IN2
  delay(2000);
}