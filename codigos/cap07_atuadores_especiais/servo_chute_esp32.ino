#include <ESP32Servo.h>

Servo servo_chute;

// Pino de controle do servo
const int PIN_SERVO = 13; // Qualquer GPIO com suporte a PWM

// Posições do mecanismo
const int POS_REPOUSO = 20;
const int POS_ARMADO  = 160;

void setup() {
  Serial.begin(115200);

  // Configura servo (define limites de pulso em microssegundos)
  servo_chute.attach(PIN_SERVO, 500, 2400);
  servo_chute.write(POS_REPOUSO);

  Serial.println("Sistema de chute ESP32 inicializado");
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

  // Armar mecanismo
  servo_chute.write(POS_ARMADO);
  delay(300);

  Serial.println("CHUTE!");

  // Liberar mola
  servo_chute.write(POS_REPOUSO);
  delay(200);

  Serial.println("Chute executado!");
}