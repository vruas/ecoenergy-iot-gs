# EcoEnergy IoT - Monitoramento Inteligente de Consumo de Energia

<p align="center">
  <img src="https://github.com/user-attachments/assets/b7479aa1-dcb1-4c9f-a202-64018a010c66" alt="Golden Data - Logo" width="200"/>
</p>


## Integrantes do Projeto

| Nome | Matrícula | Turma |
|------|-----------|-------|
| Gabriel Previ de Oliveira | 98774 | 2TDSPV |
| Gustavo Soares Fosaluza | 97850 | 2TDSPF |
| Mateus Vinicius da Conceição Silva | 551692 | 2TDSPV |
| Pedro Henrique Figueiredo de Oliveira | 552000 | 2TDSPV |
| Vitor da Silva Ruas | 550871 | 2TDSPV |


**EcoEnergy IoT** é uma solução inovadora para monitorar e gerenciar o consumo de energia de dispositivos conectados. Utilizando a tecnologia de Internet das Coisas (IoT), a solução permite medir o consumo de energia de diferentes aparelhos de forma individual, oferecendo informações detalhadas e insights para ajudar a reduzir os custos com energia elétrica.

### Link do vídeo: https://youtu.be/rGPxf3JSvnI

## Funcionalidades Principais

- **Monitoramento Individual de Dispositivos**: A solução permite monitorar o consumo de energia de cada dispositivo, como geladeiras, micro-ondas, máquinas de lavar, entre outros.
- **Cálculo de Consumo de Energia**: O sistema calcula o consumo de energia em kWh com base na potência e no tempo de uso de cada dispositivo.
- **Publicação de Dados via MQTT**: Os dados de consumo de energia são publicados em tempo real através do protocolo MQTT, permitindo fácil integração com outras plataformas de monitoramento.
- **Simulação de Dados**: Para fins de desenvolvimento e testes, os dados dos dispositivos são simulados, com consumo de energia baseado em parâmetros predefinidos como potência e tempo de uso.
- **Monitoramento via Dashboard no Node-RED**: Os dados publicados via MQTT podem ser visualizados em tempo real através de um **dashboard no Node-RED**, permitindo monitoramento e análise interativa dos dispositivos e seu consumo de energia.

## Funcionamento

1. **Coleta de Dados**: O sistema simula o monitoramento do consumo de energia de vários dispositivos. Para cada dispositivo, o sistema utiliza uma potência constante e um tempo de uso predefinido.
2. **Cálculo de Consumo**: O consumo de energia é calculado com a fórmula:

   ![image](https://github.com/user-attachments/assets/4ba544b2-a725-4693-858b-8343f816250a)


4. **Publicação via MQTT**: O consumo de energia de cada dispositivo, assim como dados de temperatura e umidade, são enviados para um broker MQTT, como o Mosquitto. Isso permite que os dados sejam acessados remotamente e integrados a outras plataformas.
5. **Monitoramento via Node-RED**: Após a publicação dos dados via MQTT, eles podem ser lidos e exibidos em tempo real por meio de um **dashboard no Node-RED**, proporcionando uma visualização interativa e em tempo real desses dados.

## Tecnologias Utilizadas

- **ESP32**: A placa microcontroladora utilizada para conectar os dispositivos à rede Wi-Fi e controlar o monitoramento.
- **DHT22**: Sensor de temperatura e umidade utilizado para fornecer dados ambientais adicionais.
- **Wi-Fi**: Conectividade de rede para enviar dados dos dispositivos para a nuvem ou outras plataformas de monitoramento.
- **MQTT**: Protocolo de mensagens para publicar os dados de consumo de energia, temperatura e umidade - Foram testados os borokers: test.mosquitto.org e broker.hivemq.com
- **Node-RED**: Plataforma para integração e criação de dashboards interativos que consome os dados via MQTT, permitindo monitoramento e controle em tempo real.

## Como Funciona?

1. **Conexão Wi-Fi**: O dispositivo ESP32 se conecta a uma rede Wi-Fi para comunicação com o broker MQTT.
2. **Simulação de Dispositivos**: O sistema simula o monitoramento do consumo de energia de dispositivos, como geladeiras, máquinas de lavar, etc.
3. **Cálculo e Publicação**: O consumo de energia é calculado e os dados são publicados via MQTT em tópicos específicos (ex: `ecoenergy/consumoEnergia`, `ecoenergy/temperatura`).
4. **Monitoramento via Node-RED**: Os dados de consumo de energia e condições ambientais (temperatura e umidade) são consumidos por um **dashboard no Node-RED**, proporcionando uma visualização interativa e em tempo real desses dados.

## Como Configurar

# Requisitos

Antes de rodar o projeto, verifique se você tem as seguintes ferramentas e dependências instaladas:

- **Visual Studio Code (VSCode)**: Para editar e gerenciar o código.
  - [Download VSCode](https://code.visualstudio.com/)
  
- **PlatformIO**: Extensão para o VSCode que facilita o desenvolvimento de projetos embarcados com ESP32.
  - [Instalar PlatformIO](https://platformio.org/install/ide?install=vscode)

- **Wokwi Simulator**: Usado para simular os circuitos e o comportamento do ESP32.
  - [Wokwi - Simulador de Circuitos](https://wokwi.com/)

## Bibliotecas do Projeto

- **WiFi**: Para conectar o ESP32 à rede Wi-Fi.
- **PubSubClient**: Para comunicação MQTT.
- **DHT**: Para utilizar o sensor DHT22.

## Fluxo e Dashboard no Node-Red:

![Captura de tela 2024-11-21 162432](https://github.com/user-attachments/assets/ae8a8d3b-8531-4bfd-afb7-1b288887f19c)

![Captura de tela 2024-11-21 162352](https://github.com/user-attachments/assets/a8c91bd4-7b0d-4499-b919-082b83e9586c)



## Instalação das Bibliotecas

Para instalar as bibliotecas no PlatformIO:

1. Abra o VSCode.
2. Vá para o painel do PlatformIO.
3. Em **PIO Home**, clique em **Libraries** e procure pelas bibliotecas:
   - **WiFi** (já incluída no pacote do ESP32)
   - **PubSubClient** (para MQTT)
   - **DHT sensor library** (para trabalhar com o DHT22)

Alternativamente, você pode adicionar as dependências diretamente no arquivo `platformio.ini`:
Exemplo:
![image](https://github.com/user-attachments/assets/4334bf53-3dac-42f1-b36e-e484cf1f3828)

**ANTES DE EXECUTAR, FAÇA A BUILD DESTE PROJETO**


