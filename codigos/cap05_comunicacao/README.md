# Capítulo 4 - Controle de Motores

Exemplos de código para controle de motores DC brushed (drivers H-Bridge) e motores brushless (ESCs).

## 📂 Arquivos

### Drivers H-Bridge (Motores DC Brushed)

**L298N:**
- [`l298n_arduino.ino`](l298n_arduino.ino) - L298N com Arduino
- [`l298n_esp32.ino`](l298n_esp32.ino) - L298N com ESP32

**TB6612FNG:**
- [`tb6612_arduino.ino`](tb6612_arduino.ino) - TB6612FNG com Arduino
- [`tb6612_esp32.ino`](tb6612_esp32.ino) - TB6612FNG com ESP32

**DRV8833 / MX1508:**
- [`mx1508_drv8833_arduino.ino`](mx1508_drv8833_arduino.ino) - DRV8833/MX1508 com Arduino
- [`mx1508_drv8833_esp32.ino`](mx1508_drv8833_esp32.ino) - DRV8833/MX1508 com ESP32

### ESCs (Motores Brushless)

**Arduino:**
- [`esc_arduino_graus.ino`](esc_arduino_graus.ino) - ESC controlado por ângulo (0-180°)
- [`esc_arduino_micros.ino`](esc_arduino_micros.ino) - ESC controlado por microssegundos (1000-2000µs)

**ESP32:**
- [`esc_esp32_graus.ino`](esc_esp32_graus.ino) - ESC controlado por ângulo (0-180°)
- [`esc_esp32_micros.ino`](esc_esp32_micros.ino) - ESC controlado por microssegundos (1000-2000µs)

## 📚 Bibliotecas

- **Arduino:** Servo (padrão)
- **ESP32:** ESP32Servo (Library Manager)

Para conceitos, configurações e detalhes técnicos, consulte o **Capítulo 4** do manual.