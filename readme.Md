# 🌐 iotFy  

## 📖 Introdução  

Agora mais maduro como desenvolvedor, estou reconstruindo meu antigo projeto **HomeYX**, agora chamado **iotFy**.  
O objetivo é continuar aprendendo programação enquanto modernizo minha casa de forma simples e econômica.  

---

## ⚙️ Setup  

- Broker **MQTT**  
- Microcontroladores **ESP**  
- Dispositivos: relés, fitas de LED, emissor IR...  

---

## 📡 Comunicação MQTT com ESPs  

Cada ESP possui um **ID único** (`espid`) e se comunica por tópicos MQTT:  

- **Receiver Topic**: `espid/receiver` → ESP recebe comandos  
- **Sender Topic**: `espid/sender` → ESP envia respostas  

**Comando não reconhecido**  
Se o ESP receber algo inválido, ele responde com a lista de comandos disponíveis.  

---

## 🔌 Controle de Relé  

**Comandos**:  
- `TURN_ON_RELAY` → Liga o relé  
- `TURN_OFF_RELAY` → Desliga o relé  
- `PULSE/{MS}` → Pulso de X ms  
- `RESTART_ESP` → Reinicia ESP  
- `STATE` → Retorna `true/false`  

---

## 🔄 Relé + Servo (Interruptor Paralelo)  

Dois ESP-01 simulam um interruptor paralelo:  

- **Main ESP (Relay Serial)** → Liga/desliga e responde a comandos.  
- **Secondary ESP (Servo)** → Age como interruptor paralelo.  

**GPIO 3 (RX)** é usado por limitação do ESP-01.  

---

## 📡 Emissor IR  

**Comando**:  
- `SEND_IR/{CODE}` → Envia código IR em HEX  

---

## 💡 Controle de Fita LED  

**Comandos**:  
- `ON` / `OFF` → Liga/Desliga  
- `SET_COLOR/{R}/{G}/{B}` → Define cor RGB  
- `SET_BRIGHTNESS/{VALUE}` → Ajusta brilho (0–255)  
- `FADE`, `SOLID_COLOR`, `WAVES`, `THEATERCHASE`, `COMET` → Efeitos visuais  
- `STATE` → Retorna estado atual (ON/OFF, cor, brilho, efeito, velocidade)  

**Parâmetros**  
- **Cor** → RGB (0–255)  
- **Brilho** → 0 a 255  
- **Velocidade** → 0 a 255 (quanto maior, mais rápido)  

---

# 🌐 iotFy  

## 📖 Introduction  

Now, as a more mature developer, I’m rebuilding my old project **HomeYX**, rebranded as **iotFy**.  
The goal is to keep learning programming while making my home smarter, integrated, and affordable.  

---

## ⚙️ Setup  

- **MQTT** broker  
- **ESP** microcontrollers  
- Devices: relays, LED strips, IR sender...  

---

## 📡 MQTT Communication with ESPs  

Each ESP has a **unique ID** (`espid`) and communicates via MQTT topics:  

- **Receiver Topic**: `espid/receiver` → ESP receives commands  
- **Sender Topic**: `espid/sender` → ESP sends responses  

**Unrecognized Command**  
If the ESP receives something invalid, it replies with the list of available commands.  

---

## 🔌 Relay Control  

**Commands**:  
- `TURN_ON_RELAY` → Turns relay ON  
- `TURN_OFF_RELAY` → Turns relay OFF  
- `PULSE/{MS}` → Pulse X ms  
- `RESTART_ESP` → Restart ESP  
- `STATE` → Returns `true/false`  

---

## 🔄 Relay + Servo (Parallel Switch)  

Two ESP-01 simulate a parallel switch:  

- **Main ESP (Relay Serial)** → Controls the relay and responds to commands.  
- **Secondary ESP (Servo)** → Works as a parallel switch.  

**GPIO 3 (RX)** is used due to ESP-01 limitation.  

---

## 📡 IR Sender  

**Command**:  
- `SEND_IR/{CODE}` → Sends IR code in HEX  

---

## 💡 LED Strip Control  

**Commands**:  
- `ON` / `OFF` → Turns ON/OFF  
- `SET_COLOR/{R}/{G}/{B}` → Set RGB color  
- `SET_BRIGHTNESS/{VALUE}` → Set brightness (0–255)  
- `FADE`, `SOLID_COLOR`, `WAVES`, `THEATERCHASE`, `COMET` → Visual effects  
- `STATE` → Returns current state (ON/OFF, color, brightness, effect, speed)  

**Parameters**  
- **Color** → RGB (0–255)  
- **Brightness** → 0 to 255  
- **Velocity** → 0 to 255 (higher = faster)  
