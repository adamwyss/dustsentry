/*
 * E18-D80NK Infrared Ranging Sensor
 * 
 *  BLUE: Ground
 * BROWN: 5v
 * BLACK: Signal
 */

#include "Samples.h"

const int MULTIPLIER = 100;
const int THRESHOLD = 20;

class InfraredDustSensor
{
  public:
    InfraredDustSensor(int pin);
    void setup();
    bool isDustbagFull();
  private:
    int _pin;
    Samples *_samples;
    
    const bool DEBUG = true;
};

InfraredDustSensor::InfraredDustSensor(int pin) {
  _pin = pin;
}

void InfraredDustSensor::setup() {
  pinMode(_pin, INPUT_PULLUP);

  _samples = new Samples(HIGH * MULTIPLIER);
}

bool InfraredDustSensor::isDustbagFull() {

  // LOW or 0 signal indicates that the sensor as detected an object.
  int signal = digitalRead(_pin);
  
  _samples->add(signal * MULTIPLIER);

  if (DEBUG) {
    _samples->println();
  }

  long avg = _samples->average();
  if (avg < THRESHOLD) {
    if (DEBUG) {
      Serial.println("InfraredDustSensor:: Signal break detected");
    }
    
    return true;
  }
  
  return false;
}
