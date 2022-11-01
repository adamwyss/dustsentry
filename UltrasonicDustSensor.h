#include "Samples.h"

const int MAX_SENSOR_VALUE = 158;

class UltrasonicDustSensor
{
  public:
    UltrasonicDustSensor(int pingPin, int echoPin);
    void setup();
    long getDistanceToBottom();
  private:
    int _pingPin;
    int _echoPin;

    Samples *_samples;

    const bool DEBUG = false;
};

long getDistanceToObjectInCentimeters(int pingPin, int echoPin);

UltrasonicDustSensor::UltrasonicDustSensor(int pingPin, int echoPin) {
  _pingPin = pingPin;
  _echoPin = echoPin;
}

void UltrasonicDustSensor::setup() {
  _samples = new Samples(MAX_SENSOR_VALUE);
}

long UltrasonicDustSensor::getDistanceToBottom() {
  long cm = getDistanceToObjectInCentimeters(_pingPin, _echoPin);
  if (cm > MAX_SENSOR_VALUE) {
    cm = MAX_SENSOR_VALUE;
  }

  _samples->add(cm);

  if (DEBUG) {
    _samples->println();
  }

  return _samples->average();
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

long getDistanceToObjectInCentimeters(int pingPin, int echoPin)
{
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   
   long duration = pulseIn(echoPin, HIGH);
   return microsecondsToCentimeters(duration);
}
