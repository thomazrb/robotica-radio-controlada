#include <Servo.h>

Servo servo_chute;

// Pino de controle do servo
const int PIN_SERVO = 9;

// Posições do servo (ajustar conforme a mecânica)
const int POS_REPOUSO = 20;   // Posição inicial (mola relaxada)
const int POS_ARMADO  = 160;  // Posição que comprime a mola

void setup() {
  Serial.begin(9600);

  // Inicializa servo
  servo_chute.attach(PIN_SERVO);
  servo_chute.write(POS_REPOUSO);

  Serial.println("Sistema de chute com servo inicializado");
  Serial.println("Envie 'C' para chutar");
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();

    if (comando == 'C' || comando == 'c') {
      executar_chute();
    }
  }
}

void executar_chute() {
  Serial.println("Preparando chute...");

  // 1. Move servo para armar a mola
  servo_chute.write(POS_ARMADO);
  delay(300); // Aguarda o servo atingir a posição

  Serial.println("CHUTE!");

  // 2. Retorna rapidamente para liberar a mola
  servo_chute.write(POS_REPOUSO);
  delay(200);

  Serial.println("Chute executado!");
}