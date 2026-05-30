// ============================================================
//  ESP32 — Servidor WebSocket
//  SENAI XR Lab · Luciano Trevisan
// ============================================================
//  O HTML agora está no GitHub Pages:
//  https://luctrevisan.github.io/esp32xr/
//
//  Este sketch só precisa:
//    - Conectar ao Wi-Fi
//    - Enviar dados do potenciômetro via WebSocket
//
//  Biblioteca necessária (Library Manager):
//    - WebSockets  by Markus Sattler
// ============================================================

#include <WiFi.h>
#include <WebSocketsServer.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

// ── ALTERE AQUI ──────────────────────────────────────────────
const char* ssid     = "VIVOFIBRA-9350";
const char* password = "9CADF0E3A3";
// ─────────────────────────────────────────────────────────────

const int PINO_POT = 34;   // GPIO34 — pino analógico

WebSocketsServer ws(81);

void onWsEvent(uint8_t client, WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_CONNECTED) {
    Serial.printf("[WS] Cliente %u conectado — IP: %s\n",
      client, ws.remoteIP(client).toString().c_str());
  } else if (type == WStype_DISCONNECTED) {
    Serial.printf("[WS] Cliente %u desconectado\n", client);
  }
}

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);  // evita reset por brownout
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao Wi-Fi");
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (++tentativas > 40) {
      Serial.println("\nFalha — verifique ssid/password e reinicie.");
      while (true) delay(1000);
    }
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());
  Serial.println("─────────────────────────────────────────");
  Serial.println("Abra no browser:");
  Serial.println("https://luctrevisan.github.io/esp32xr/");
  Serial.println("─────────────────────────────────────────");
  Serial.println("Atualize ESP32_IP no index.html com o IP acima.");

  ws.begin();
  ws.onEvent(onWsEvent);
  Serial.println("WebSocket aguardando na porta 81...");
}

void loop() {
  ws.loop();

  // Lê potenciômetro e normaliza 0.0 → 1.0
  int   leitura = analogRead(PINO_POT);
  float valor   = leitura / 4095.0;

  // Envia JSON para todos os browsers conectados
  String json = "{\"valor\":" + String(valor, 3) + "}";
  ws.broadcastTXT(json);

  delay(100);  // 10 leituras por segundo
}
