#include <Arduino.h>
#include <WiFi.h>
#include <DHTesp.h>
#include <PubSubClient.h>

// Configurações de WiFi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = ""; // Substitua pela sua senha

// Configurações de MQTT
const char *BROKER_MQTT = "test.mosquitto.org";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "esp32_mqtt";
const char *ECOENERGY_TEMP = "ecoenergy/temperatura";
const char *ECOENERGY_HUMI = "ecoenergy/umidade";
const char *ECOENERGY_DEVICE = "ecoenergy/dispositivo";
const char *ECOENERGY_ENERGY = "ecoenergy/consumoEnergia";

// Configurações de Hardware
#define PIN_DHT 12
#define SENSOR_READ_DELAY 2000       
#define DEVICE_MONITOR_INTERVAL 2000  // Atualizar a cada 2 segundos

// Variáveis globais
WiFiClient espClient;
PubSubClient MQTT(espClient);
DHTesp dht;
unsigned long deviceChangeTime = 0;
TempAndHumidity sensorValues;

struct Dispositivo {
  String nome;
  int potencia;  // em Watts
  float tempoUso; // em horas
};

Dispositivo dispositivos[] = {
  {"Geladeira", 150, 24},
  {"Máquina de Lavar", 500, 1},
  {"Microondas", 1000, 0.5},
  {"Chuveiro", 5500, 0.25},
  {"Lâmpada", 60, 6},
  {"Televisão", 100, 4},
  {"Ar Condicionado", 1000, 8},
  {"Computador", 200, 8},
  {"Ferro de Passar", 1000, 0.5}
};

Dispositivo dispositivoAtual; // Variável para armazenar o dispositivo atual

float calcularConsumoEnergia(int potencia, float tempoUso) {
  return (potencia * tempoUso) / 1000.0;
}

void publicarDadosDispositivo() {
  // Publicando consumo de energia do dispositivo atual
  float consumo = calcularConsumoEnergia(dispositivoAtual.potencia, dispositivoAtual.tempoUso);
  
  // Publicando o consumo de energia como texto simples
  char consumoEnergia[10];
  snprintf(consumoEnergia, sizeof(consumoEnergia), "%.2f", consumo);  // Formata o valor como texto simples

  if (MQTT.publish(ECOENERGY_ENERGY, consumoEnergia)) {
    Serial.println("Consumo de energia publicado com sucesso!");
  } else {
    Serial.println("Falha ao publicar consumo de energia.");
  }

  // Publicando o nome do dispositivo
  if (MQTT.publish(ECOENERGY_DEVICE, dispositivoAtual.nome.c_str())) {
    Serial.println("Nome do dispositivo publicado com sucesso!");
  } else {
    Serial.println("Falha ao publicar nome do dispositivo.");
  }

  Serial.println(">> Resumo do Consumo:");
  Serial.println("   - Dispositivo: " + dispositivoAtual.nome);
  Serial.println("   - Consumo    : " + String(consumo) + " kWh");
  Serial.println("========================================");
}

void publicarSensores() {
  // Publica a leitura dos sensores (temperatura e umidade)
  String temperatura = String(sensorValues.temperature);
  if (MQTT.publish(ECOENERGY_TEMP, temperatura.c_str())) {
    Serial.println("Temperatura publicada com sucesso!");
  } else {
    Serial.println("Falha ao publicar temperatura.");
  }

  String umidade = String(sensorValues.humidity);
  if (MQTT.publish(ECOENERGY_HUMI, umidade.c_str())) {
    Serial.println("Umidade publicada com sucesso!");
  } else {
    Serial.println("Falha ao publicar umidade.");
  }

  // Exibição dos dados no Serial Monitor
  Serial.println("\n");
  Serial.println("########################################");
  Serial.println("       [Leitura dos Sensores]");
  Serial.println("########################################");
  Serial.println(">> Temperatura Ambiente: " + temperatura);
  Serial.println(">> Umidade Relativa    : " + umidade);
  Serial.println("########################################");
}

void updateSensorValues() {
  sensorValues = dht.getTempAndHumidity();
}

void initWiFi() {
  Serial.print("Conectando com a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("...");
  }

  Serial.println("\nConectado com sucesso!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
    } else {
      Serial.println("Falha ao conectar. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void checkWiFiAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print("...");
    }
    Serial.println("\nWiFi reconectado!");
  }
  if (!MQTT.connected()) reconnectMQTT();
}

void selecionarDispositivoAleatorio() {
  // Seleciona um dispositivo aleatório da lista
  int indiceAleatorio = random(0, sizeof(dispositivos) / sizeof(dispositivos[0]));
  dispositivoAtual = dispositivos[indiceAleatorio];

  // Exibe os dados do novo dispositivo no Serial Monitor
  Serial.println("\n");
  Serial.println("========================================");
  Serial.println("        [Monitoramento de Dispositivo]");
  Serial.println("========================================");
  Serial.println(">> Novo dispositivo monitorado:");
  Serial.println("   - Nome       : " + dispositivoAtual.nome);
  Serial.println("   - Potência   : " + String(dispositivoAtual.potencia) + " W");
  Serial.println("   - Tempo de Uso: " + String(dispositivoAtual.tempoUso) + " horas");
  Serial.println("========================================");
  Serial.println("\n");

  // Publica os dados do novo dispositivo
  publicarDadosDispositivo();
}

void setup() {
  Serial.begin(115200);
  dht.setup(PIN_DHT, DHTesp::DHT22);
  initWiFi();
  initMQTT();

  // Inicializa o primeiro dispositivo aleatório
  selecionarDispositivoAleatorio();
}

void loop() {
  checkWiFiAndMQTT();
  MQTT.loop();

  unsigned long now = millis();

  // Atualiza a cada 2 segundos
  if (now - deviceChangeTime >= DEVICE_MONITOR_INTERVAL) {
    // Atualiza a leitura dos sensores a cada 2 segundos
    updateSensorValues();
    publicarSensores();
    
    // Seleciona um dispositivo aleatório e publica os dados
    selecionarDispositivoAleatorio();

    deviceChangeTime = now;
  }
}
