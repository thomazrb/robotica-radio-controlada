// Pinos para o Motor A
const int ENA = 14; // Pino de Velocidade (PWM)
const int IN1 = 27; // Direção 1
const int IN2 = 26; // Direção 2

const int freq = 30000;
const int resolucao = 8;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // IMPORTANTE: Remova o jumper físico do pino ENA no driver 
  // para conectar este fio, senão o controle de velocidade não funciona.
  ledcAttach(ENA, freq, resolucao);
}

void loop() {
  // Mover para frente (Velocidade média)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(ENA, 128); // 0-255 (Meia velocidade)
  delay(2000);

  // Parar (Freio motor)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH); 
  ledcWrite(ENA, 0);
  delay(1000);
}