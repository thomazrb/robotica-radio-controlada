// Pinos para o Motor A
const int ENA = 9;  // Pino PWM
const int IN1 = 8;  // Direção 1
const int IN2 = 7;  // Direção 2

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop() {
  // Mover para frente (Velocidade média)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 128); // 0-255 (Meia velocidade)
  delay(2000);

  // Parar (Freio motor)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 0);
  delay(1000);
}