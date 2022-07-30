
#include <SoftwareSerial.h>
#include <Servo.h>

#define BT_TX_PIN 3
#define BT_RX_PIN 2
#define BT_PIN 13

#define DIST_TRIG_PIN 6
#define DIST_ECHO_PIN 7
#define DIST_CONSTANT 0.017

#define HEAT_PIN A0
#define HEAT_CONSTANT 0.48828125

#define LIGHT_PIN A2

#define RED_LIGHT_PIN 11
#define GREEN_LIGHT_PIN 10
#define BLUE_LIGHT_PIN 9

#define SERVO_PIN 4


//#include "DHT.h"
//DHT dht(HEAT_PIN, DHT11);
SoftwareSerial BT(BT_TX_PIN, BT_RX_PIN); // TX, RX on arduino (RX, Tx on bluetooth)
Servo myservo;

void setup()
{
  // Blutooth
  pinMode(13, OUTPUT);
  Serial.println("Hello");
  BT.begin(9600);

  // Distance sensor
  pinMode(DIST_TRIG_PIN, OUTPUT);
  pinMode(DIST_ECHO_PIN, INPUT);

  // Heat sensor
  pinMode(HEAT_PIN, INPUT);

  // Serial
  Serial.begin(9600);

  // RGB led
  pinMode(RED_LIGHT_PIN, OUTPUT);
  pinMode(GREEN_LIGHT_PIN, OUTPUT);
  pinMode(BLUE_LIGHT_PIN, OUTPUT);

  //Servo
   myservo.attach(SERVO_PIN);

}

// ========== DISTANCE ==========

float distanceSensor()
{
  // Ensure that we're not pulsing
  digitalWrite(DIST_TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send pulse for 10ms
  digitalWrite(DIST_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(DIST_TRIG_PIN, LOW);

  // Read result from echo and return in cm
  float duration = pulseIn(DIST_ECHO_PIN, HIGH); // High = 38ms
  return duration * DIST_CONSTANT;
}

// ========== HEAT ==========

//float heatSensor()
//{
//  return analogRead(HEAT_PIN) * HEAT_CONSTANT;
//  return dht.readTemperature();
//}

// ========== LIGHT ==========

int lightSensor()
{
  return analogRead(LIGHT_PIN);
}
// RGB colors
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(RED_LIGHT_PIN, red_light_value);
  analogWrite(GREEN_LIGHT_PIN, green_light_value);
  analogWrite(BLUE_LIGHT_PIN, blue_light_value);
}
// ========== MAIN ==========

void loop()
{
  char cmd;
  float distance = distanceSensor();
//  float temperature = heatSensor();
  int light = lightSensor();
//

    Serial.print("Distance (cm): ");
    distance >= 400 || distance <= 2 ? Serial.print("Out of range") : Serial.print(distance)  ;

  
    distance <= 20 ? RGB_color(255, 0, 0) : RGB_color(0, 255, 0); // Red : Green
 


  if (BT.available())
  {

    cmd = BT.read();
    // Serial.println(cmd);

    switch (cmd)
    {
    case '1': // On
      Serial.println("Executing case 1");
      myservo.write(180);
      break;

    case '2': // Off
      Serial.println("Executing case 2");
      myservo.write(180);
      break;

    case '3':
//      Serial.println("Executing case 3");
//      Serial.print(", temperature (C): ");
//      isnan(temperature) ? Serial.print("Error") : Serial.print(temperature);
      break;

    case '4':
      Serial.println("Executing case 4");
      break;

    case '5':
      Serial.println("Executing case 5");
      break;

    default:
      Serial.println("Executing default case");
    }
  }
}
