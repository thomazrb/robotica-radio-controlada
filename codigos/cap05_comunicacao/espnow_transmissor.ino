#include <WiFi.h>
#include <esp_now.h>

// ==================== Definição de pinos ====================
#define JOY_LX 34   // ADC
#define JOY_LY 35   // ADC
#define JOY_RX 32   // ADC
#define JOY_RY 33   // ADC

#define BTN_A 25
#define BTN_B 26

// ==================== Parâmetros ====================
#define DEADZONE 100   // Zona morta do joystick (ADC)

// ==================== Estrutura de dados ====================
typedef struct {
  int16_t lx;
  int16_t ly;
  int16_t rx;
  int16_t ry;
  uint16_t buttons;
} ControlData;

ControlData comandos;

// Endereço MAC do ESP32 receptor (robô)
uint8_t receptorMAC[] = {0x24, 0x6F, 0x28, 0xAB, 0xCD, 0xEF};

// ==================== Callback de envio ====================
void onDataSent(const uint8_t *mac, esp_now_send_status_t status) {
  if (status != ESP_NOW_SEND_SUCCESS) {
    Serial.println("Falha no envio ESP-NOW");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  Serial.print("MAC do Transmissor: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }

  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receptorMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);

  Serial.println("Transmissor ESP-NOW pronto");
}

void loop() {
  // Leitura dos joysticks (ADC 12 bits)
  int16_t lx = analogRead(JOY_LX) - 2048;
  int16_t ly = analogRead(JOY_LY) - 2048;
  int16_t rx = analogRead(JOY_RX) - 2048;
  int16_t ry = analogRead(JOY_RY) - 2048;

  // Deadzone
  if (abs(lx) < DEADZONE) lx = 0;
  if (abs(ly) < DEADZONE) ly = 0;
  if (abs(rx) < DEADZONE) rx = 0;
  if (abs(ry) < DEADZONE) ry = 0;

  comandos.lx = lx;
  comandos.ly = ly;
  comandos.rx = rx;
  comandos.ry = ry;

  comandos.buttons = 0;
  if (!digitalRead(BTN_A)) comandos.buttons |= 0x01;
  if (!digitalRead(BTN_B)) comandos.buttons |= 0x02;

  esp_now_send(receptorMAC, (uint8_t*)&comandos, sizeof(comandos));

  delay(20); // 50 Hz
}