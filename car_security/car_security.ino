const int biometrico = 13;
const int cartao = 12;
const int sensorPorta = 11;
const int ledOK = 10;
const int ledWarn = 9;
const int bomba = 8;

int estadodaporta = 1;
int estadodocartao = 0;
int estadodobiometrico = 0;
int estadodabomba = 0;
int ledOKState = LOW;
int ledWarnState = LOW;
unsigned long previousMillis = 0;
boolean cartaoLido = false;
boolean biometria = false;
boolean sempreLigado = false;
boolean portaFechada = true;

void setup() {
  pinMode(biometrico, INPUT);
  pinMode(cartao, INPUT);
  pinMode(sensorPorta, INPUT);
  pinMode(ledOK, OUTPUT);
  pinMode(ledWarn, OUTPUT);
  pinMode(bomba, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  verificaCartao();
  verificaDigital();
  estadodaporta = digitalRead(sensorPorta);
  if(estadodaporta == LOW || portaFechada == false) {
    portaFechada = false;
    if(portaFechada == false) {
      portaAberta(currentMillis);
    }
    
    if(sempreLigado) {
      digitalWrite(ledWarn, LOW);
    } else {
      digitalWrite(ledWarn, HIGH);
    }
  }
}

void portaAberta(unsigned long currentMillis) {
  if(biometria || cartaoLido || sempreLigado) {
    digitalWrite(ledOK, HIGH);
    return;
  }
  
  if(currentMillis - previousMillis >= 80000) {
    previousMillis = currentMillis;
    digitalWrite(bomba, LOW);
    digitalWrite(ledOK, LOW);
  }
}

void verificaCartao() {
  estadodocartao = digitalRead(cartao);
  if(estadodocartao == HIGH) {
    digitalWrite(bomba, HIGH);
    digitalWrite(ledOK, HIGH);
    digitalWrite(ledWarn, LOW);
    cartaoLido = true;
    sempreLigado = true;
    portaFechada = true;
  } else {
    cartaoLido = false;
  }
}

void verificaDigital() {
  estadodobiometrico = digitalRead(biometrico);
  if(estadodobiometrico == HIGH) {
    digitalWrite(bomba, HIGH);
    digitalWrite(ledOK, HIGH);
    digitalWrite(ledWarn, LOW);
    biometria = true;
    portaFechada = true;
  } else {
    biometria = false;
  }
}