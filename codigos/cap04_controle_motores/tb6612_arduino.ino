// Definição dos pinos (TB6612 + Arduino)
const int PIN_PWMA = 9;   // Pino PWM
const int PIN_AIN1 = 8;   // Direção
const int PIN_AIN2 = 7;   // Direção
const int PIN_STBY = 6;   // Standby

void setup() {
  pinMode(PIN_AIN1, OUTPUT);
  pinMode(PIN_AIN2, OUTPUT);
  pinMode(PIN_STBY, OUTPUT);

  digitalWrite(PIN_STBY, HIGH); // Habilita o driver
}

void loop() {
  moverFrente(255); // Velocidade máxima
  delay(2000);
  frear();
  delay(1000);
}

void moverFrente(int velocidade) {
  digitalWrite(PIN_AIN1, HIGH);
  digitalWrite(PIN_AIN2, LOW);
  analogWrite(PIN_PWMA, velocidade); // 0--255
}

void frear() {
  digitalWrite(PIN_AIN1, HIGH);
  digitalWrite(PIN_AIN2, HIGH); // Freio eletrônico
  analogWrite(PIN_PWMA, 0);
}