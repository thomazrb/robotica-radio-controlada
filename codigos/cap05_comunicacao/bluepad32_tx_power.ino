#include <esp_bt.h>
#include <Bluepad32.h>

void setup() {
  Serial.begin(115200);
  
  // IMPORTANTE: Configurar potência ANTES de inicializar Bluepad32
  
  // Para BLE (Bluetooth Low Energy - ESP32, ESP32-S3, ESP32-C3)
  sp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9);
  
  // Para Bluetooth Clássico (BR/EDR - usado por gamepads)
  esp_bredr_tx_power_set(ESP_PWR_LVL_P9, ESP_PWR_LVL_P9);
  
  // Agora inicializa Bluepad32
  BP32.setup(&onConnectedController, &onDisconnectedController);
  
  Serial.println("Potência Bluetooth configurada para +9 dBm");
}