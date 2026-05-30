# SENAI XR Lab — ESP32 + Babylon.js

Projeto educacional de **Realidade Virtual/Aumentada com IoT** desenvolvido para o curso de Mecatrônica Industrial do SENAI Centro de Formação Profissional Antonio Adolpho Lobbe — São Carlos, SP.

---

## Estrutura do repositório

```
esp32xr/
├── index.html              ← Aplicação WebXR (hospedada no GitHub Pages)
├── assets/
│   └── models/
│       └── engrenagem.glb  ← Modelo 3D da engrenagem
├── firmware/
│   └── esp32_senai_xr.ino  ← Sketch do ESP32 (só WebSocket)
└── README.md
```

---

## Como funciona

```
Potenciômetro (GPIO34)
    ↓  analogRead() a cada 100ms
ESP32 — WebSocket porta 81
    ↓  JSON: {"valor": 0.742}
Browser (PC / Meta Quest Pro)
    ↓  GitHub Pages (HTTPS) → Babylon.js
Cena 3D — engrenagem gira, cor muda, RPM sobe
```

---

## Configuração

### 1 — Firmware (ESP32)

Abra `firmware/esp32_senai_xr.ino` no Arduino IDE e altere:

```cpp
const char* ssid     = "NOME_DO_SEU_WIFI";
const char* password = "SENHA_DO_SEU_WIFI";
```

Carregue no ESP32. O Serial Monitor (115200 baud) mostrará o IP do dispositivo.

### 2 — Frontend (index.html)

Após carregar o firmware, anote o IP exibido no Serial Monitor e atualize no `index.html`:

```javascript
const ESP32_IP = "192.168.X.XXX";  // IP do seu ESP32
```

Faça commit da alteração para o repositório.

### 3 — GitHub Pages

- Settings → Pages → Source: `main` / `/ (root)`
- Acesse: `https://luctrevisan.github.io/esp32xr/`

---

## Hardware necessário

| Componente | Conexão |
|---|---|
| ESP32 DOIT DevKit V1 | — |
| Potenciômetro 10kΩ | Pino central → GPIO34 · Extremos → 3.3V e GND |

---

## Visualização

| Dispositivo | Como acessar |
|---|---|
| PC / notebook | Abre `https://luctrevisan.github.io/esp32xr/` no Chrome |
| Celular | Mesmo URL, cena 3D flat |
| Meta Quest Pro | Meta Browser → mesmo URL → botão `[ VR IMERSIVO ]` ou `[ AR PASSTHROUGH ]` |

---

## O que o potenciômetro controla

- Velocidade de rotação da engrenagem
- Intensidade do spot vermelho (iluminação)
- Emissão de partículas/faíscas (acima de 60%)
- RPM simulado (0 a 3600)
- Temperatura simulada (20 a 80°C)

---

## Próximos passos (roteiro de evolução)

- [ ] Múltiplos sensores no JSON (temperatura real, corrente)
- [ ] MQTT via Raspberry Pi como broker
- [ ] Hand tracking no Quest Pro
- [ ] Gêmeo digital com modelo completo da bancada

---

**SENAI · Mecatrônica Industrial · São Carlos · SP**
