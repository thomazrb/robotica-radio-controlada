// ===============================
// CONFIGURAÇÕES
// ===============================

// Pino de controle do solenoide
// Arduino: qualquer pino digital
// ESP32: qualquer GPIO digital
const int PIN_SOLENOIDE = 9;

// Configurações de tempo (em milissegundos)
const unsigned long DURACAO_PULSO = 100;   // 100 ms = suficiente para chute
const unsigned long INTERVALO_MIN = 2000;  // 2 segundos entre chutes

// ===============================
// VARIÁVEIS DE CONTROLE
// ===============================

unsigned long ultimo_acionamento = 0;
bool pode_acionar = true;

// ===============================
// SETUP
// ===============================

void setup() {
  Serial.begin(115200);   // Funciona tanto no Arduino quanto no ESP32
  
  pinMode(PIN_SOLENOIDE, OUTPUT);
  digitalWrite(PIN_SOLENOIDE, LOW); // Garante estado inicial desligado
  
  Serial.println("Sistema de chute inicializado");
  Serial.println("Envie 'C' para chutar");
}

// ===============================
// LOOP PRINCIPAL
// ===============================

void loop() {
  // Verifica se recebeu comando via Serial
  if (Serial.available() > 0) {
    char comando = Serial.read();
    
    if (comando == 'C' || comando == 'c') {
      acionar_chute();
    }
  }
  
  // Libera novo chute após intervalo mínimo
  if (!pode_acionar && millis() - ultimo_acionamento >= INTERVALO_MIN) {
    pode_acionar = true;
    Serial.println("Sistema pronto para próximo chute");
  }
}

// ===============================
// FUNÇÃO DE CHUTE
// ===============================

void acionar_chute() {
  if (!pode_acionar) {
    Serial.println("AVISO: Aguarde antes de chutar novamente!");
    return;
  }
  
  Serial.println("CHUTE!");
  
  // Aciona solenoide
  digitalWrite(PIN_SOLENOIDE, HIGH);
  delay(DURACAO_PULSO);
  digitalWrite(PIN_SOLENOIDE, LOW);
  
  // Bloqueia novos acionamentos temporariamente
  ultimo_acionamento = millis();
  pode_acionar = false;
  
  Serial.print("Próximo chute em ");
  Serial.print(INTERVALO_MIN / 1000);
  Serial.println(" segundos");
}