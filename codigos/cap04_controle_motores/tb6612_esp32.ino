// Definição dos pinos (TB6612 + ESP32)
const int PIN_PWMA = 16;
const int PIN_AIN1 = 17;
const int PIN_AIN2 = 18;
const int PIN_STBY = 19; // Standby

const int freq = 30000;   // Frequência do PWM (30 kHz)
const int resolucao = 8;  // Resolução em bits

void setup() {
  pinMode(PIN_AIN1, OUTPUT);
  pinMode(PIN_AIN2, OUTPUT);
  pinMode(PIN_STBY, OUTPUT);

  digitalWrite(PIN_STBY, HIGH); // Habilita o driver

  // Configura o PWM (Arduino-ESP32 Core v3.0+)
  ledcAttach(PIN_PWMA, freq, resolucao);
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
  ledcWrite(PIN_PWMA, velocidade);
}

void frear() {
  digitalWrite(PIN_AIN1, HIGH);
  digitalWrite(PIN_AIN2, HIGH); // Freio eletrônico
  ledcWrite(PIN_PWMA, 0);
}