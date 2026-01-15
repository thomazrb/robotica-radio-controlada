// === Configuração da Dabble ===
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

void setup() {
  Serial.begin(9600);

  // Inicializa Dabble com baud rate do HM-10
  // RX = pino 2, TX = pino 3
  Dabble.begin(9600, 2, 3);

  Serial.println("Dabble iniciado. Conecte o smartphone.");
}

void loop() {
  // Atualiza estado da comunicação BLE
  Dabble.processInput();

  // Verifica se o GamePad está conectado
  if (!GamePad.isConnected()) {
    return;
  }

  // Botões direcionais
  if (GamePad.isUpPressed()) {
    Serial.println("UP pressionado - Robô FRENTE");
  }

  if (GamePad.isDownPressed()) {
    Serial.println("DOWN pressionado - Robô TRÁS");
  }

  if (GamePad.isLeftPressed()) {
    Serial.println("LEFT pressionado - Robô ESQUERDA");
  }

  if (GamePad.isRightPressed()) {
    Serial.println("RIGHT pressionado - Robô DIREITA");
  }

  // Leitura do joystick analógico (valores de -7 a +7)
  int joyX = GamePad.getXaxisData();
  int joyY = GamePad.getYaxisData();

  if (joyX != 0 || joyY != 0) {
    Serial.print("Joystick X: ");
    Serial.print(joyX);
    Serial.print(" | Y: ");
    Serial.println(joyY);
  }

  delay(20); // ~50 Hz
}