#ifndef SAMPLES_H
#define SAMPLES_H

const int MAX_VALUES = 10;

class Samples
{
  public:
    Samples(long initialValue);

    void add(long value);
    long average();
    void println();
  private:
  
    int _index;
    long _samples[MAX_VALUES];

    long _total;
};

Samples::Samples(long initialValue) {
  _index = 0;
  for (int i = 0; i < MAX_VALUES; i++) {
    _samples[i] = initialValue;
  }
  
  _total = initialValue * MAX_VALUES;
}

void Samples::add(long value) {
  _total -= _samples[_index];
  _samples[_index] = value;
  _total += _samples[_index];
  
  _index++;
  if (_index >= MAX_VALUES) {
    _index = 0;
  }
}

long Samples::average() {
  return _total / long(MAX_VALUES);
}

void Samples::println() {
  long avg = this->average();
  Serial.print(avg);
  Serial.print(" = [");
  for (int i = 0; i < MAX_VALUES; i++) {
    Serial.print(_samples[i]);
    if (i != MAX_VALUES - 1) {
      Serial.print(",");
    }
  }
  Serial.println("]");
}

#endif
