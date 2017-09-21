#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

const int LED = 13;
//const int LDR = A0;
int entrada = 0;
const int SENSOR A0;

byte mac [] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x24}
IPAddress server(192, 162, 0, 105);

EthernetClient ethClient;
PubSubClient client;

void setup() {
  pinMode(SENSOR, INPUT);
  Serial.begin(9600);
  client.setServer(server, 1883);
  Ethernet.begin(mac);
  delay(1500);
  Serial.println(Ethernet.localIP());
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);
}

void reconnect(){
  while(! client.connected()){
    Serial.println("Tentando se conectar ao MQTT");  
    if(client.connect("arduino24")){
      Serial.println("Conectado com sucesso!");
    }else{
      Serial.println("Erro ao tentar se conectar!");
      delay(5000);
    }
  }
 }

void loop() {

  entrada = analogRead(LDR);
  
  delay(500);

  if (entrada < 160) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  delay(1000);
  Serial.println(entrada);

  
  if(!client.connected){
   reconnect();
  }
   
  client.loop();
  
  float valorDoSensor = analogRead(SENSOR);
  char txtValorDoSensor[4];
  dtostrf(valorDoSensor, 4, 0, txtValorDoSensor);
  client.publish("mazola", txtValorDoSensor);
}
