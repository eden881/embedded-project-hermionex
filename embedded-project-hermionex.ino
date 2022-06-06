#define DIST_TRIG_PIN 2
#define DIST_ECHO_PIN 4
#define DIST_CONSTANT 0.017

#define HEAT_PIN A0
#define HEAT_CONSTANT 0.48828125

#define LIGHT_PIN A2

#include "DHT.h"
DHT dht(HEAT_PIN, DHT11);

void setup() {
  // Distance sensor
  pinMode(DIST_TRIG_PIN, OUTPUT);
  pinMode(DIST_ECHO_PIN, INPUT);

  // Heat sensor
  pinMode(HEAT_PIN, INPUT);
  dht.begin();

  // Light sensor
  pinMode(LIGHT_PIN, INPUT);

  // Serial
  Serial.begin(9600);
}

// ========== DISTANCE ==========

float distanceSensor() {
  // Ensure that we're not pulsing
  digitalWrite(DIST_TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send pulse for 10ms
  digitalWrite(DIST_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(DIST_TRIG_PIN, LOW);

  // Read result from echo and return in cm
  float duration = pulseIn(DIST_ECHO_PIN, HIGH);  // High = 38ms
  return duration * DIST_CONSTANT;
}

// ========== HEAT ==========

float heatSensor() {
  //return analogRead(HEAT_PIN) * HEAT_CONSTANT;
  return dht.readTemperature();
}

// ========== LIGHT ==========

int lightSensor() {
  return analogRead(LIGHT_PIN);
}

// ========== MAIN ==========

void loop() {
  // Data calculation
  float distance = distanceSensor();
  float temperature = heatSensor();
  int light = lightSensor();

  // Print results
  Serial.print("Distance (cm): ");
  distance >= 400 || distance <= 2 ? Serial.print("Out of range") : Serial.print(distance);
  Serial.print(", temperature (C): ");
  isnan(temperature) ? Serial.print("Error") : Serial.print(temperature);
  Serial.print(", light: ");
  Serial.println(light);

  // Delay
  delay(200);
}
