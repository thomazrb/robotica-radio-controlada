#include <SoftwareSerial.h>

// Configuração dos pinos de comunicação
// Pino 2 do Arduino = RX (recebe do TX do módulo)
// Pino 3 do Arduino = TX (envia para RX do módulo via divisor)
SoftwareSerial bluetooth(2, 3); 

// Pinos de controle do driver de motor (exemplo: L298N)
const int MOTOR_ESQ_IN1 = 5;
const int MOTOR_ESQ_IN2 = 6;
const int MOTOR_DIR_IN1 = 9;
const int MOTOR_DIR_IN2 = 10;

// Função auxiliar: parar todos os motores
void pararMotores() {
  digitalWrite(MOTOR_ESQ_IN1, LOW);
  digitalWrite(MOTOR_ESQ_IN2, LOW);
  digitalWrite(MOTOR_DIR_IN1, LOW);
  digitalWrite(MOTOR_DIR_IN2, LOW);
}

void setup() {
  Serial.begin(9600);       // Monitor Serial (debug via USB)
  bluetooth.begin(9600);    // Comunicação com módulo Bluetooth
  
  // Configura pinos dos motores
  pinMode(MOTOR_ESQ_IN1, OUTPUT);
  pinMode(MOTOR_ESQ_IN2, OUTPUT);
  pinMode(MOTOR_DIR_IN1, OUTPUT);
  pinMode(MOTOR_DIR_IN2, OUTPUT);

  // Garante estado inicial seguro
  pararMotores();
  
  Serial.println("Sistema iniciado. Aguardando conexão Bluetooth...");
}

void loop() {
  // Verifica se chegou algum comando do smartphone
  if (bluetooth.available()) {
    char comando = bluetooth.read();

    // Ignora caracteres de controle comuns (newline, carriage return)
    if (comando == '\n' || comando == '\r') {
      return;
    }

    // Failsafe simples: parar antes de processar novo comando
    pararMotores();
    
    switch (comando) {
      case 'F': // Frente
        Serial.println("Comando: FRENTE");
        digitalWrite(MOTOR_ESQ_IN1, HIGH);
        digitalWrite(MOTOR_ESQ_IN2, LOW);
        digitalWrite(MOTOR_DIR_IN1, HIGH);
        digitalWrite(MOTOR_DIR_IN2, LOW);
        break;
        
      case 'T': // Trás
        Serial.println("Comando: TRÁS");
        digitalWrite(MOTOR_ESQ_IN1, LOW);
        digitalWrite(MOTOR_ESQ_IN2, HIGH);
        digitalWrite(MOTOR_DIR_IN1, LOW);
        digitalWrite(MOTOR_DIR_IN2, HIGH);
        break;
        
      case 'E': // Esquerda
        Serial.println("Comando: ESQUERDA");
        digitalWrite(MOTOR_ESQ_IN1, LOW);
        digitalWrite(MOTOR_ESQ_IN2, HIGH);
        digitalWrite(MOTOR_DIR_IN1, HIGH);
        digitalWrite(MOTOR_DIR_IN2, LOW);
        break;
        
      case 'D': // Direita
        Serial.println("Comando: DIREITA");
        digitalWrite(MOTOR_ESQ_IN1, HIGH);
        digitalWrite(MOTOR_ESQ_IN2, LOW);
        digitalWrite(MOTOR_DIR_IN1, LOW);
        digitalWrite(MOTOR_DIR_IN2, HIGH);
        break;
        
      case 'P': // Parar
        Serial.println("Comando: PARAR");
        // pararMotores() já foi chamado
        break;
        
      default:
        Serial.print("Comando desconhecido: ");
        Serial.println(comando);
        // Mantém motores parados por segurança
    }
    
    // Envia confirmação de volta ao smartphone
    bluetooth.print("OK: ");
    bluetooth.println(comando);
  }
}