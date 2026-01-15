#include <Bluepad32.h>

// MAC address do controle autorizado (AA:BB:CC:DD:EE:FF)
uint8_t allowedMAC[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

ControllerPtr myController = nullptr;

void onConnectedController(ControllerPtr ctl) {
  ControllerProperties properties = ctl->getProperties();
  bd_addr_t btAddr = properties.btaddr;

  Serial.print("Controle tentando conectar: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", btAddr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();

  // Verifica whitelist
  bool authorized = true;
  for (int i = 0; i < 6; i++) {
    if (btAddr[i] != allowedMAC[i]) {
      authorized = false;
      break;
    }
  }

  if (authorized && myController == nullptr) {
    Serial.println("Controle AUTORIZADO conectado");
    myController = ctl;

    // Feedback visual (se suportado)
    ctl->setColorLED(0, 255, 0);
  } else {
    Serial.println("Controle NÃO AUTORIZADO - Desconectando");

    // Feedback visual (se suportado)
    ctl->setColorLED(255, 0, 0);

    // Desconexão imediata (sem delay em callback)
    ctl->disconnect();
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  if (myController == ctl) {
    Serial.println("Controle autorizado desconectado");
    myController = nullptr;
  }
}

void setup() {
  Serial.begin(115200);

  Serial.println("Sistema com Whitelist MAC ativada");
  Serial.print("Controle autorizado: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", allowedMAC[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();

  BP32.setup(&onConnectedController, &onDisconnectedController);
}

void loop() {
  BP32.update();

  // Processa comandos apenas do controle autorizado
  if (myController && myController->isConnected() && myController->hasData()) {
    // Código de controle do robô aqui
  }

  delay(10);
}