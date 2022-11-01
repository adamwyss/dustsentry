
#include "WarningLight.h"
#include "UltrasonicDustSensor.h"
#include "InfraredDustSensor.h"

const int RELAY_PIN = 5;
WarningLight light(RELAY_PIN);

const int SENSOR_PIN = 2;
InfraredDustSensor sensor(SENSOR_PIN);

//const int TRIGGER_PIN = 7;
//const int ECHO_PIN = 6;
//UltrasonicDustSensor sensor2(TRIGGER_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);

  light.setup();
  sensor.setup();
  Serial.println("startup complete!");
}

void loop() {
  bool full = sensor.isDustbagFull();
  if (full && light.isOff()){
    Serial.println("DustSentry:: Dustbag FULL; warning light");
    light.request(on);
  }
  else if (!full && light.isOn()) {
     Serial.println("DustSentry:: Dustbag EMPTY; no warning light");
     light.request(off);
  }

  light.update();
  delay(500);
}
