#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// ----- Pines HC-SR04 -----
// Sensor 1: saludo
const int TRIG1_PIN = 22;
const int ECHO1_PIN = 24;

// Sensor 2: sentado
const int TRIG2_PIN = 30;
const int ECHO2_PIN = 32;

// ----- Rango típico MG996R -----
const int MIN_US   = 600;
const int MAX_US   = 2400;
const int FRAME_US = 20000;

// ----- Canales / posiciones de la pata frontal derecha -----
const int FR_LIFT_CH      = 5;
const int FR_LIFT_STAND   = 160;
const int FR_LIFT_RAISED  = 180;

const int FR_SWING_CH     = 6;
const int FR_SWING_STAND  = 80;

// ------------ Funciones Auxiliares ------------
int usToTicks(int us) {
  return constrain((long)us * 4096L / FRAME_US, 0, 4095);
}

int degToTicks(int deg) {
  deg = constrain(deg, 0, 180);
  int us = map(deg, 0, 180, MIN_US, MAX_US);
  return usToTicks(us);
}

void setDeg(int channel, int deg) {
  pwm.setPWM(channel, 0, degToTicks(deg));
}

// Poner robot en posición de parado
void poseParado() {
  // Frontal Izq
  setDeg(0, 100);
  setDeg(1, 30);
  setDeg(2, 100);

  // Frontal Derecha
  setDeg(4, 100);
  setDeg(FR_LIFT_CH,  FR_LIFT_STAND);
  setDeg(FR_SWING_CH, FR_SWING_STAND);

  // Trasera Izq
  setDeg(8, 95);
  setDeg(9, 40);
  setDeg(10, 90);

  // Trasera Der
  setDeg(13, 100);
  setDeg(14, 150);
  setDeg(15, 100);
}

// Medir distancia en cm para un par de pines
long medirDistanciaCm(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000);
  if (duracion == 0) return -1;

  long distancia = duracion * 0.0343 / 2.0;
  return distancia;
}

// Secuencia de saludo (sensor 1)
void hacerSaludo() {
  // Levantar pata
  setDeg(FR_LIFT_CH, FR_LIFT_RAISED);
  delay(500);

  // Swing
  setDeg(FR_SWING_CH, 180);
  delay(500);

  setDeg(FR_SWING_CH, 160);
  delay(500);

  setDeg(FR_SWING_CH, FR_SWING_STAND);
  delay(500);

  // Bajar pata
  setDeg(FR_LIFT_CH, FR_LIFT_STAND);
  delay(500);
}

// Secuencia de sentado (sensor 2)
void hacerSentado() {
  // Pata trasera izquierda
  setDeg(9, 20);    // de 40 → 20
  setDeg(10, 135);  // de 90 → 135

  // Pata trasera derecha
  setDeg(14, 170);  // de 150 → 170
  setDeg(15, 50);   // de 100 → 50

  // Mantenerse sentado 5 segundos
  delay(5000);

  // Volver a posición parado
  poseParado();
}

void setup() {
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);

  // Sensor 1
  pinMode(TRIG1_PIN, OUTPUT);
  pinMode(ECHO1_PIN, INPUT);
  digitalWrite(TRIG1_PIN, LOW);

  // Sensor 2
  pinMode(TRIG2_PIN, OUTPUT);
  pinMode(ECHO2_PIN, INPUT);
  digitalWrite(TRIG2_PIN, LOW);

  poseParado();
}

void loop() {
  static unsigned long ultimoSinDeteccion1 = millis();
  static unsigned long ultimoSinDeteccion2 = millis();

  // Sensor 1: saludo
  long d1 = medirDistanciaCm(TRIG1_PIN, ECHO1_PIN);
  if (d1 > 0 && d1 < 30) {
    if (millis() - ultimoSinDeteccion1 >= 5000) {
      hacerSaludo();
    }
    ultimoSinDeteccion1 = millis();
  }

  // Sensor 2: sentado
  long d2 = medirDistanciaCm(TRIG2_PIN, ECHO2_PIN);
  if (d2 > 0 && d2 < 30) {
    if (millis() - ultimoSinDeteccion2 >= 5000) {
      hacerSentado();
    }
    ultimoSinDeteccion2 = millis();
  }

  delay(100);
}
