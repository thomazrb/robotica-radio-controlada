// Pinos conectados aos canais do receptor
const int PIN_CH1 = 2;  // Canal 1
const int PIN_CH2 = 3;  // Canal 2

// Pinos de saída PWM para driver de motor
const int MOTOR_ESQ_PWM = 9;
const int MOTOR_DIR_PWM = 10;

void setup() {
  Serial.begin(9600);
  
  // Configura pinos do receptor como entrada
  pinMode(PIN_CH1, INPUT);
  pinMode(PIN_CH2, INPUT);
  
  // Configura pinos do motor como saída
  pinMode(MOTOR_ESQ_PWM, OUTPUT);
  pinMode(MOTOR_DIR_PWM, OUTPUT);
}

void loop() {
  // Lê largura do pulso do receptor (em microssegundos)
  unsigned long ch1 = pulseIn(PIN_CH1, HIGH, 25000); // timeout 25ms
  unsigned long ch2 = pulseIn(PIN_CH2, HIGH, 25000);
  
  // Valida se recebeu sinal válido (entre 1000-2000µs)
  if (ch1 < 1000 || ch1 > 2000) ch1 = 1500; // Neutro se inválido
  if (ch2 < 1000 || ch2 > 2000) ch2 = 1500;
  
  // Converte para range do analogWrite (0-255)
  // 1000µs -> 0, 1500µs -> 127, 2000µs -> 255
  int motor_esq = map(ch1, 1000, 2000, 0, 255);
  int motor_dir = map(ch2, 1000, 2000, 0, 255);
  
  // Envia PWM aos motores
  analogWrite(MOTOR_ESQ_PWM, motor_esq);
  analogWrite(MOTOR_DIR_PWM, motor_dir);
  
  // Debug no Serial Monitor
  Serial.print("CH1: "); Serial.print(ch1);
  Serial.print(" | CH2: "); Serial.println(ch2);
  
  delay(20); // Loop a cada 20ms (50 Hz)
}
