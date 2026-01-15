// Pinos conectados aos canais do receptor
const int PIN_CH1 = 16;
const int PIN_CH2 = 17;

// Variáveis para armazenar tempos
volatile unsigned long ch1_start = 0;
volatile unsigned long ch1_width = 1500; // Default: neutro

volatile unsigned long ch2_start = 0;
volatile unsigned long ch2_width = 1500;

// Funções de interrupção (ISR)
void IRAM_ATTR isrCH1() {
  if (digitalRead(PIN_CH1) == HIGH) {
    ch1_start = micros(); // Marca início do pulso
  } else {
    ch1_width = micros() - ch1_start; // Calcula duração
  }
}

void IRAM_ATTR isrCH2() {
  if (digitalRead(PIN_CH2) == HIGH) {
    ch2_start = micros();
  } else {
    ch2_width = micros() - ch2_start;
  }
}

void setup() {
  Serial.begin(115200);
  
  // Configura pinos como entrada
  pinMode(PIN_CH1, INPUT);
  pinMode(PIN_CH2, INPUT);
  
  // Ativa interrupções em ambas as bordas (subida e descida)
  attachInterrupt(digitalPinToInterrupt(PIN_CH1), isrCH1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_CH2), isrCH2, CHANGE);
  
  Serial.println("Sistema iniciado - Lendo canais PWM");
}

void loop() {
  unsigned long ch1_copy, ch2_copy;

  // Cópia atômica das variáveis compartilhadas
  noInterrupts();
  ch1_copy = ch1_width;
  ch2_copy = ch2_width;
  interrupts();

  int ch1 = constrain(ch1_copy, 1000, 2000);
  int ch2 = constrain(ch2_copy, 1000, 2000);

  Serial.print("CH1: "); Serial.print(ch1);
  Serial.print(" µs | CH2: "); Serial.print(ch2);
  Serial.println(" µs");

  delay(100);
}