#include <Servo.h>
#include <SoftwareSerial.h>
 
#define BT_TX_PIN 4
#define BT_RX_PIN 2
#define BT_PIN 13

#define DIST_TRIG_PIN 2
#define DIST_ECHO_PIN 4
#define DIST_CONSTANT 0.017

#define HEAT_PIN A0
#define HEAT_CONSTANT 0.48828125

#define LIGHT_PIN A2

#include "DHT.h"
DHT dht(HEAT_PIN, DHT11);

void setup() {
  // Blutooth
  SoftwareSerial BT(BT_TX_PIN, BT_RX_PIN); // TX, RX on arduino (RX, Tx on bluetooth)
  pinMode(13,OUTPUT);
  Serial.println("Hello");
  BT.begin(9600);
  BT.print("Hello"); //Test
   
  // Distance sensor
  pinMode(DIST_TRIG_PIN, OUTPUT);
  pinMode(DIST_ECHO_PIN, INPUT);

  // Heat sensor
  pinMode(HEAT_PIN, INPUT);

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

void loop(){
  char cmd;
  float distance = distanceSensor();
  float temperature = heatSensor();
  int light = lightSensor();

  Serial.print("Distance (cm): ");
  distance >= 400 || distance <= 2 ? Serial.print("Out of range") : Serial.print(distance);
  
  if (BT.available()){
   cmd=BT.read();
   //Serial.println(cmd);
   switch(cmd) {
      case 1: // On
        myservo.write(180);
        break;
       
      case 2: // Off
        myservo.write(180);
        break;
       
      case 3:
        Serial.print(", temperature (C): ");
        isnan(temperature) ? Serial.print("Error") : Serial.print(temperature);        
        break;
       
      case 4:
        // code block
        break;
       
      case 5:
        // code block
        break;
       
      default:
        // code block
  }
}
