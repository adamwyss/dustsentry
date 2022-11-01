/*
 * 
 */
 
const int REQUIRED_TIME_IN_STATE = 5000;

enum warningState {
  on,
  off
};

class WarningLight
{
  public:
    WarningLight(int pin);
    void setup();
    bool isOn();
    bool isOff();
    void request(warningState newState);
    void update();
  private:
    int _pin;
    unsigned long _last;
    warningState _current;
    warningState _desired;

    const bool DEBUG = false;
};

WarningLight::WarningLight(int pin) {
  _pin = pin;
  _current = off;
  _desired = off;
  _last = millis();
}

void WarningLight::setup() {
  pinMode(_pin, OUTPUT);
}

bool WarningLight::isOn() {
  return _desired == on;
}

bool WarningLight::isOff() {
  return _desired == off;
}

String stringForState(warningState state)
{
  return state == on ? "ON" : "OFF";
}

void WarningLight::request(warningState newState) {
  if (DEBUG && newState != _desired) {
    Serial.print("WarningLight::desired := ");
    Serial.println(stringForState(newState));
  }
  
  _desired = newState;
}

void WarningLight::update() {
  unsigned long now = millis();
  unsigned long timeInState = now - _last;

  // *** unsigned, this should not work ***
  if (timeInState < 0) {
    // Hmm, we have detected a rollover 
    // we will say we have been in our current state since 0
    _last = 0;
    timeInState = now;
  }

  if (DEBUG) {
    Serial.print("WarningLight:: Desired = ");
    Serial.print(stringForState(_desired)); 
    Serial.print("; Current = ");
    Serial.println(stringForState(_current));
  }

  if (timeInState < REQUIRED_TIME_IN_STATE) {
    if (DEBUG) {
      Serial.print("WarningLight:: Ignoring - Time In State: ");
      Serial.print(timeInState);
      Serial.println("ms");
    }
    
    return;
  }

  if (_current != _desired) {
    if (DEBUG) {
      Serial.print("WarningLight::UpdatingState new state: ");
      Serial.println(stringForState(_current));
    }
      
    _current = _desired;
    _last = millis();
    digitalWrite(_pin, _current == on ? HIGH : LOW);
  }
}
