#include <SoftwareSerial.h>

// HM-10 conectado nos pinos 2 (RX) e 3 (TX)
SoftwareSerial ble(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  ble.begin(9600); // HM-10 padrão: 9600 bps
  
  Serial.println("Sistema BLE iniciado");
}

void loop() {
  if (ble.available()) {
    char cmd = ble.read();

    // Ignora caracteres de controle comuns
    if (cmd == '\n' || cmd == '\r') {
      return;
    }

    // Processa comando
    // (Mesmo protocolo do exemplo Bluetooth Clássico)
    Serial.print("Comando recebido via BLE: ");
    Serial.println(cmd);

    // Aqui entraria a lógica de controle do robô
    // (motores, servos, modos de operação, etc.)
  }
}