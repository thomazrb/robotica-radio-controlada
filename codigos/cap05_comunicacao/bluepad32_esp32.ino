#include <Bluepad32.h>

ControllerPtr myController = nullptr;

// Callback chamado quando um controle conecta
void onConnectedController(ControllerPtr ctl) {
  if (myController == nullptr) {
    Serial.println("Controle conectado!");

    ControllerProperties properties = ctl->getProperties();
    Serial.printf("Modelo: %s\n", ctl->getModelName().c_str());
    Serial.printf("VID: 0x%04x, PID: 0x%04x\n",
                  properties.vendor_id, properties.product_id);

    myController = ctl;
  } else {
    Serial.println("Já existe um controle conectado. Ignorando...");
  }
}

// Callback chamado quando um controle desconecta
void onDisconnectedController(ControllerPtr ctl) {
  if (myController == ctl) {
    Serial.println("Controle desconectado!");

    // IMPORTANTE: aqui deve-se parar todos os motores
    // por segurança (failsafe)
    myController = nullptr;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Bluepad32 - Controle de Robô");
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());

  const uint8_t* addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %02X:%02X:%02X:%02X:%02X:%02X\n",
                addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  BP32.setup(&onConnectedController, &onDisconnectedController);

  // Desabilita mouse/touchpad virtual
  BP32.enableVirtualDevice(false);

  Serial.println("\nAguardando conexão do controle...");
}

void loop() {
  // Atualiza estado interno do Bluepad32
  BP32.update();

  if (!myController || !myController->isConnected()) {
    // Nenhum controle conectado -> robô deve permanecer parado
    return;
  }

  // === Leitura dos sticks analógicos ===
  int leftX = myController->axisX();
  int leftY = myController->axisY();

  // Zona morta para evitar drift
  const int DEADZONE = 50;

  if (abs(leftY) > DEADZONE || abs(leftX) > DEADZONE) {
    int motorLeft = leftY - leftX;
    int motorRight = leftY + leftX;

    motorLeft = constrain(motorLeft, -512, 512);
    motorRight = constrain(motorRight, -512, 512);

    int pwmLeft = map(abs(motorLeft), 0, 512, 0, 255);
    int pwmRight = map(abs(motorRight), 0, 512, 0, 255);

    Serial.printf("Motores: L=%d (%s) | R=%d (%s)\n",
                  pwmLeft, (motorLeft > 0 ? "FWD" : "REV"),
                  pwmRight, (motorRight > 0 ? "FWD" : "REV"));
  } else {
    Serial.println("PARADO");
  }

  // Botão A: arma
  if (myController->a()) {
    Serial.println("Botão A: ARMA ATIVADA");
  }

  // Botão B: emergência
  if (myController->b()) {
    Serial.println("Botão B: EMERGÊNCIA");
  }

  delay(10); // ~100 Hz (evitar delays maiores)
}