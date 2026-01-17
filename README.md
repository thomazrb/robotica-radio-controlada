# Robótica Rádio Controlada: Manual de Construção para Futebol e Combate

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Arduino](https://img.shields.io/badge/Arduino-Compatible-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![ESP32](https://img.shields.io/badge/ESP32-Compatible-E7352C?logo=espressif&logoColor=white)](https://www.espressif.com/)
[![Language](https://img.shields.io/badge/Language-C%2FC++-blue?logo=cplusplus)](https://isocpp.org/)
[![Version](https://img.shields.io/badge/Version-1.0-green)](https://github.com/thomazrb/robotica-radio-controlada/releases)
[![Status](https://img.shields.io/badge/Status-Active-success)](https://github.com/thomazrb/robotica-radio-controlada)

Manual técnico prático sobre robótica rádio controlada focado em aplicações reais para robôs de futebol (categoria 500g) e robôs de combate (categoria beetleweight 1,4kg) rádio controlados, nas competições existentes no IFES Campus São Mateus.

## Sobre o Manual

Este manual nasceu da necessidade de consolidar conhecimento prático e testado em campo. Diferentemente de muitos materiais acadêmicos, prioriza a aplicação prática sobre teoria pura. As recomendações são baseadas em componentes reais, normalmente testados em competições, com preços e disponibilidade considerando a realidade do mercado brasileiro.

O conteúdo está organizado de forma progressiva: começamos pelos fundamentos (microcontroladores, baterias, motores) e avançamos para sistemas mais complexos (controle de motores, comunicação wireless, conversores de nível lógico e atuadores especiais).

**Público-alvo:** Estudantes de engenharia e cursos técnicos, entusiastas de robótica e competidores.

## Conteúdo do Manual

### Capítulo 1: Microcontroladores
Comparação detalhada entre Arduino (Uno, Nano, Micro) e ESP32 (Standard, C3, S3 Super Mini). Análise de especificações técnicas, vantagens e limitações de cada plataforma. Inclui tabelas comparativas, fluxograma de decisão e recomendações por aplicação considerando conectividade, canais RMT para ESCs, consumo energético e restrições de espaço/peso.

### Capítulo 2: Baterias e Gerenciamento de Energia
Conceitos fundamentais (tensão, capacidade, taxa C, configuração série/paralelo). Análise detalhada de pilhas alcalinas, bateria 9V, NiMH, Li-ion (18650, power banks) e LiPo. Cálculo de autonomia, carregamento seguro, proteção contra sobre-descarga, reguladores de tensão (linear vs switching, Mini560 Pro). Solução para resets do ESP32 (brownout): capacitores de desacoplamento, circuito com diodo Schottky e filtragem contra ruído de motores.

### Capítulo 3: Motores
Conceitos fundamentais (tensão, RPM, torque, corrente de stall, redução). Motores DC brushed: N20, TT (amarelinho) e 25GA370 com análise detalhada de especificações, preços e aplicações. Encoders integrados vs discos furados externos (quando usar e quando não usar em projetos RC). Motores brushless: nomenclatura (XXYY-ZZ), KV rating, aplicações em tração e armas rotativas. Guia de seleção por categoria de robô (futebol 500g, combate antweight/beetleweight) e por orçamento. Acoplamento mecânico: direto, correia, tangenciamento (friction drive) com vantagens/desvantagens de cada método.

### Capítulo 4: Controle de Motores
Conceitos fundamentais: Ponte H (H-Bridge) e PWM (duty cycle, frequência). Drivers para motores brushed: L298N (legado), TB6612FNG (moderno), DRV8833 e MX1508 (baixa tensão). Tabela comparativa entre drivers. ESCs para motores brushless: PWM padrão (servomotor style), ESCs bidirecionais, calibração e arming. Protocolos digitais: DShot com verificação de erros (CRC). Periférico RMT do ESP32 para timing preciso. Exemplos práticos completos para Arduino e ESP32 com todos os drivers e protocolos, incluindo controle bidirecional e failsafe.

### Capítulo 5: Comunicação
Sistemas RC profissionais (FlySky, RadioLink): vantagens, leitura de canais PWM no microcontrolador. Módulos Bluetooth para Arduino: HC-05/HC-06 (Clássico), HM-10/HC-08 (BLE), biblioteca Dabble. Apps de smartphone (gamepad virtual). ESP32 com Bluetooth integrado: biblioteca Bluepad32 para controles físicos (PlayStation, Xbox, Nintendo, 8BitDo), tabela de compatibilidade por modelo de ESP32, whitelist MAC, configuração de potência TX, desabilitação de WiFi. ESP-NOW: protocolo proprietário de alta performance (baixa latência), arquitetura com joysticks analógicos customizados, transmissor e receptor, failsafe. Arquitetura PC-in-the-loop para telemetria avançada. Comparação ESP-NOW vs Bluetooth vs RC comercial.

### Capítulo 6: Conversão de Nível Lógico
O problema 3.3V (ESP32) vs 5V (Arduino/sensores): tabela comparativa de níveis lógicos, risco de dano permanente ao ESP32. Solução 1: Divisor resistivo de tensão (valores práticos 1kΩ/2kΩ, quando usar, limitações de impedância e ruído eletromagnético). Solução 2: Módulos conversores bidirecionais LLC (BSS138 MOSFET, pinagem, pull-ups integrados, cuidados com I²C). Casos especiais: drivers de motor (L298N/TB6612 aceitam 3.3V diretamente), LEDs WS2812B (compatibilidade com 3.3V), ESCs e DShot (evitar conversores lentos). Tabela resumo de quando converter. Checklist de segurança e ordem de preferência das soluções.

### Capítulo 7: Atuadores Especiais
Diferença entre atuadores e motores de locomoção. Solenoides lineares: princípio de funcionamento (bobina, êmbolo, mola), JF0530B para robôs de futebol, circuito de acionamento com transistor MOSFET (IRLZ44N logic-level), diodo de proteção, duty cycle crítico (10%). Servomotores: princípio de funcionamento (motor DC + redução + potenciômetro + controle), controle por PWM (1000-2000µs), tipos (padrão, rotação contínua, digitais), SG90 especificações. Sistema de chute com servo + mola: mecanismo de armamento e liberação, calibração, controle de força variável. Exemplos de código para Arduino e ESP32. Tabela comparativa solenoide vs servo para chute. Outras aplicações: flipadores, pan-tilt, garras, levantadores. Fluxograma de decisão para seleção de atuadores.

## Códigos de Exemplo

Este repositório contém todos os códigos apresentados no manual, organizados por capítulo:

- **[Capítulo 4 - Controle de Motores](codigos/cap04_controle_motores/)**: Exemplos com drivers L298N, TB6612, DRV8833, MX1508 e ESCs
- **[Capítulo 5 - Comunicação](codigos/cap05_comunicacao/)**: Bluetooth (HC-05, HM-10), Bluepad32, ESP-NOW e rádios RC
- **[Capítulo 7 - Atuadores Especiais](codigos/cap07_atuadores_especiais/)**: Solenoides e servomotores para chute

Todos os códigos são compatíveis com **Arduino IDE** e desenvolvidos para **Arduino e/ou ESP32** (conforme indicado no nome do arquivo).

## Como Usar os Códigos

1. **Clone este repositório:**
   ```bash
   git clone https://github.com/thomazrb/robotica-radio-controlada.git
   ```

2. **Abra o código desejado na Arduino IDE**

3. **Instale os cores necessários (se usar ESP32):**
   - **Core ESP32 padrão:** Instale via Board Manager (buscar por "esp32" da Espressif)
   - **Core Bluepad32:** Instalação separada via URL customizada no Board Manager (ver instruções no Capítulo 5)
   
   **Nota:** Bluepad32 é um **core modificado** do ESP32 (não é biblioteca), necessário apenas para códigos de controles Bluetooth

4. **Instale as bibliotecas necessárias (quando aplicável):**
   - ESP32Servo (para servos no ESP32)
   - Dabble (para app Dabble)
   - WiFi + esp_now (já incluídas no core ESP32)

4. **Selecione a placa correta:**
   - Arduino: `Tools > Board > Arduino AVR Boards > Arduino Uno` (ou modelo específico)
   - ESP32 padrão: `Tools > Board > esp32 > ESP32 Dev Module` (ou modelo específico)
   - ESP32 com Bluepad32: `Tools > Board > esp32_bluepad32 > ESP32 Dev Module` (requer instalação do core Bluepad32 - ver Capítulo 5)

5. **Ajuste os pinos conforme seu hardware** (números de GPIO/pinos digitais)

6. **Compile e faça upload!**

## Requisitos

### Hardware Mínimo
- Microcontrolador: Arduino ou ESP32
- Bateria: Dimensionada conforme a aplicação
- Motores: conforme aplicação (DC brushed ou brushless)
- Driver de motor: conforme os motores escolhidos

### Software
- [Arduino IDE](https://www.arduino.cc/en/software) 2.x
- [Drivers CP210x/CH340](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) (se necessário)
- Core ESP32 para Arduino IDE (se usar ESP32)

## Estrutura do Repositório

```
robotica-radio-controlada/
├── README.md                     # Este arquivo
├── LICENSE                       # Licença MIT
├── codigos/
│   ├── cap04_controle_motores/   # 10 arquivos
│   ├── cap05_comunicacao/        # 11 arquivos
│   └── cap07_atuadores_especiais/ # 3 arquivos
```

## Onde Comprar o Manual

**Status:** Em breve

O manual completo será disponibilizado em formato **ebook** e **paperback** através da Amazon Kindle Direct Publishing (KDP).

## Especificações Técnicas do Manual

- **Páginas:** ~186 (incluindo diagramas e códigos)
- **Formato ebook (PDF):** A4 ou similar (formato digital flexível)
- **Formato paperback:** 15,24 x 22,86 cm (6" x 9")
- **Idioma:** Português (Brasil)
- **Edição:** 1ª edição (Janeiro 2026)

## Autor

**Thomaz Rodrigues Botelho**

Engenheiro com experiência prática em robótica competitiva, especialmente em competições de futebol de robôs e combate de robôs.

## Contribuições

Encontrou algum erro no código ou tem sugestões de melhoria?

1. Abra uma [Issue](https://github.com/thomazrb/robotica-radio-controlada/issues)
2. Ou envie um Pull Request com a correção

Toda contribuição é bem-vinda!

## Licença

Os códigos deste repositório são distribuídos sob a licença **MIT** (veja [LICENSE](LICENSE)).

O conteúdo textual do manual está protegido por direitos autorais © 2026 Thomaz Rodrigues Botelho.

## Aviso Legal

As informações contidas neste repositório e no manual são fornecidas "como estão", sem garantias de qualquer tipo. A construção de robôs de combate envolve riscos inerentes. Siga sempre as normas de segurança e regulamentos aplicáveis.

---

⚡ **Os circuitos funcionam, os códigos compilam, e as especificações são realistas.** ⚡

*Bem-vindo ao mundo da robótica rádio controlada!*