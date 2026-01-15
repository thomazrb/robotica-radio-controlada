#include <WiFi.h>
#include <Bluepad32.h>

void setup() {
  Serial.begin(115200);

  // IMPORTANTE:
  // Desabilitar completamente o Wi-Fi antes de inicializar a Bluepad32
  WiFi.disconnect(true, true);
  WiFi.mode(WIFI_OFF);

  // Inicializa Bluepad32 (Bluetooth é gerenciado internamente)
  BP32.setup(&onConnectedController, &onDisconnectedController);

  Serial.println("Wi-Fi desabilitado. Apenas Bluetooth ativo.");

  // Resto da inicialização...
}