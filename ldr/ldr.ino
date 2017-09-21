const int LED = 13;
const int LDR = A0;
int entrada = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);
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
  
}
