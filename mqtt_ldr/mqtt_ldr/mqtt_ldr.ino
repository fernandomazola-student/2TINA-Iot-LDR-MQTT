#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

const int LED = 13;
const int LDR = A0;
int entrada = 0;




byte mac [] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x24};
IPAddress server(192, 162, 0, 105);

EthernetClient ethClient;
PubSubClient client(ethClient);

void setup() {
  pinMode(LDR, INPUT);
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

  if(!client.connected()){
   reconnect();
  }
   
  client.loop();

  entrada = analogRead(LDR);

  delay(1000);
  Serial.println(entrada);

  char txtValorDoSensor[4];
  dtostrf(entrada, 4, 0, txtValorDoSensor);
  client.publish("mazola", txtValorDoSensor);
}
