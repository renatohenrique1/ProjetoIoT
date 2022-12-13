// ===================
// Incluir bibliotecas
// ===================
#include <ESP8266WiFi.h> //inclui suporte ao NodeMCU
#include <PubSubClient.h> //inclui suporte ao MQTT no HiveMQ Cloud

// =======================
// Definicoes e constantes
// =======================

// Configuracoes da rede WiFi
const char* ssid = "Net-Virtua-3709-2.4G"; //SSID da rede WiFi
const char* password = "4011437090"; //senha da rede WiFi

const char* mqtt_server = "mqtt://broker.hivemq.com:1883"; //URL do broker MQTT
const int mqtt_server_port = 1883; //porta do broker MQTT

// Variaveis globais e objetos
#define MSG_BUFFER_SIZE (500) //define MSG_BUFFER_SIZE como 500
WiFiClient client; //cria o objeto client
PubSubClient mqtt_client(client); //cria o objeto mqtt_client
long lastMsg = 0;

String clientID = "ESP8266Client-"; //identificacao do cliente

String topicoPrefixo = "MACK42005426"; //para o prefixo do topico, utilizar MACK seguido do TIA
String topicoTodos = topicoPrefixo + "/#"; //para retornar todos os topicos
String topico_0 = topicoPrefixo + "/hello"; //topico para teste
String mensagem_0 = "NodeMCU Connected"; //mensagem para o topico 0
String topico_1 = topicoPrefixo + "/sensor1"; //topico para o sensor 1
String mensagem_1 = ""; //mensagem para o topico 1
String topico_2 = topicoPrefixo + "/atuador1"; //topico para o atuador 1
String mensagem_2 = ""; //mensagem para o topico 2
String mensagemTemp = ""; //armazena temporariamente as mensagens recebidas via MQTT

//int estadoBotao = 0; //variavel que le o estado atual do botao conectado em D0
//int ultimoEstadoBotao = 0; //variavel que guarda o ultimo estado do botao conectado em D0
//int controlaEstadoBotao = 0; //variavel que controla o estado do botao conectado em D0

// ==============================
// Funcoes definidas pelo usuario
// ==============================

// Funcao para configurar a conexao WiFi
void setup_wifi() {
  //WiFi.mode(WIFI_STA); //ativa o modo de estacao
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

// Funcao para receber mensagens
void callback(char* topic, byte* payload, unsigned int length) {
  mensagemTemp = "";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    mensagemTemp += (char)payload[i];
  }

  if (String(topic) == topico_2) {
    mensagem_2 = mensagemTemp;
  }

  Serial.println();
}

// Funcao para conectar no broker MQTT
void reconnect() {
  // Loop until we’re reconnected
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection…");

	// Create a random client ID
    randomSeed(micros()); //inicializa a semente do gerador de numeros aleatorios
    clientID += String(random(0xffff), HEX);

	// Attempt to connect
    if (mqtt_client.connect(clientID.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqtt_client.publish(topico_0.c_str(), mensagem_0.c_str());
      // ... and resubscribe
      mqtt_client.subscribe(topicoTodos.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}	

// =======
// setup()
// =======

void setup() {
  //verificar os PINOS que serao utilizados no sketch
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, INPUT); //pino zero, onde esta ligado o pushbutton
  pinMode(D1, OUTPUT); //pino 1, onde esta ligado o LED
  Serial.begin(9600); //inicializa a saida serial
  setup_wifi();

  mqtt_client.setServer(mqtt_server, mqtt_server_port); //configura a conexao com o broker MQTT
  mqtt_client.setCallback(callback); //configura o recebimento de mensagens
}

// ======
// loop()
// ======

void loop() {
  if (!mqtt_client.connected()) {
    reconnect();
  }
  mqtt_client.loop(); //processa as mensagens e mantem a conexao com o broker MQTT

  //nesta parte colocar a leitura do sensor de temperatura
float sVoltage;



void setup() 

{

  Serial.begin(9600);

  pinMode(D1, OUTPUT);

  StartMQTT();

}

}

void loop()      

{

  ConsultaConexoes();

  float xVal = analogRead(sensorPin);



  sVoltage = (xVal*3100.0)/1023;



  tempC = sVoltage;

  Serial.print("A temperatura é de = ");

  Serial.println(tempC);

  delay(3000);



  digitalWrite(D0, HIGH);

  delay(1000);



  digitalWrite(D0, LOW);

  delay(1000);



  sprintf(msg, "%d", tempC);

  

  MQTT.publish(TOPICO_PUBLISH_SENSOR_TEMP, msg);

  MQTT.loop();

  delay(3000);

}
  //mensagem_1 = valor lido do sensor de temperatura

  //Publica mensagem
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    mqtt_client.publish(topico_1.c_str(), mensagem_1.c_str());
  }
  
  //Subscreve mensagem
  //A subscricao eh realizada na funcao reconnect(),
  //e o recebimento das mensagens na funcao callback().
  //Para filtrar as mensagens dos topicos, verificar a funcao callback().

}
