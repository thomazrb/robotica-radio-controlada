#include <WiFi.h>
#include <esp_now.h>

// ==================== Definição de pinos ====================
#define MOTOR_ESQ_PWM 25
#define MOTOR_DIR_PWM 26

#define MOTOR_ESQ_DIR 27
#define MOTOR_DIR_DIR 14

#define CANAL_ESQ 0
#define CANAL_DIR 1

#define PWM_FREQ 20000
#define PWM_RES  8

// ==================== Parâmetros ====================
#define FAILSAFE_TIMEOUT 100   // ms
#define DEADZONE 50

// ==================== Estrutura ====================
typedef struct {
  int16_t lx;
  int16_t ly;
  int16_t rx;
  int16_t ry;
  uint16_t buttons;
} ControlData;

volatile ControlData comandos;
volatile unsigned long lastPacketTime = 0;

// ==================== Callback ====================
void onDataReceive(const uint8_t *mac, const uint8_t *data, int len) {
  if (len == sizeof(ControlData)) {
    memcpy((void*)&comandos, data, sizeof(ControlData));
    lastPacketTime = millis();
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_ESQ_DIR, OUTPUT);
  pinMode(MOTOR_DIR_DIR, OUTPUT);

  ledcSetup(CANAL_ESQ, PWM_FREQ, PWM_RES);
  ledcSetup(CANAL_DIR, PWM_FREQ, PWM_RES);

  ledcAttachPin(MOTOR_ESQ_PWM, CANAL_ESQ);
  ledcAttachPin(MOTOR_DIR_PWM, CANAL_DIR);

  WiFi.mode(WIFI_STA);
  Serial.print("MAC do Receptor: ");
  Serial.println(WiFi.macAddress());

  esp_now_init();
  esp_now_register_recv_cb(onDataReceive);

  Serial.println("Receptor ESP-NOW pronto (failsafe ativo)");
}

void loop() {
  // FAILSAFE
  if (millis() - lastPacketTime > FAILSAFE_TIMEOUT) {
    ledcWrite(CANAL_ESQ, 0);
    ledcWrite(CANAL_DIR, 0);
    return;
  }

  int lx = comandos.lx;
  int ly = comandos.ly;

  if (abs(lx) < DEADZONE) lx = 0;
  if (abs(ly) < DEADZONE) ly = 0;

  int forward = map(ly, -2048, 2047, -255, 255);
  int turn    = map(lx, -2048, 2047, -255, 255);

  int pwmEsq = constrain(forward + turn, -255, 255);
  int pwmDir = constrain(forward - turn, -255, 255);

  // Motor Esquerdo
  digitalWrite(MOTOR_ESQ_DIR, pwmEsq >= 0 ? HIGH : LOW);
  ledcWrite(CANAL_ESQ, abs(pwmEsq));

  // Motor Direito
  digitalWrite(MOTOR_DIR_DIR, pwmDir >= 0 ? HIGH : LOW);
  ledcWrite(CANAL_DIR, abs(pwmDir));

  delay(10);
}