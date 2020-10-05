#include <Servo.h>

const int SW = 2;
const int PIN_SERVO = 9;
const int VRY = A4;
const int VRX = A5;

const int CLOSE = 170;
const int OPEN = 90;

int leitura_vrx;
int leitura_vry;
int leitura_sw;
int posi_atual = 520;
boolean abrir = 0;
boolean fechar = 0;

Servo servo_motor;

void setup() {
  
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT_PULLUP);
  servo_motor.attach(PIN_SERVO);
  
}

void loop() {

  leitura_vry = analogRead(VRY);
  leitura_vrx = analogRead(VRX);
  leitura_vrx = map(leitura_vrx, 0, 1023, CLOSE, OPEN);
  servo_motor.write(leitura_vrx);
  delay(10);

  if (leitura_vry >= 550) {
    abrir = 1;
  }
  else if (leitura_vry <= 490) {
    fechar = 1;
  }
  while (abrir == 1) {
    leitura_vry = analogRead(VRY);
    leitura_sw = digitalRead(SW);

    if (leitura_sw == HIGH) {
      if (leitura_vry > posi_atual) {
        posi_atual = leitura_vry;
        leitura_vry = map(leitura_vry, 0, 1023, CLOSE, OPEN);
        servo_motor.write(leitura_vry);
      }
    }
    else {
      abrir = 0;
      posi_atual = 520;
    }
  }

  while (fechar == 1) {
    leitura_vry = analogRead(VRY);
    leitura_sw = digitalRead(SW);

    if (leitura_sw == HIGH) {
      if (leitura_vry < posi_atual) {
        posi_atual = leitura_vry;
        leitura_vry = map(leitura_vry, 0, 1023, CLOSE, OPEN);
        servo_motor.write(leitura_vry);
      }
    }
    else {
      fechar = 0;
      posi_atual = 520;
    }
  }
}
