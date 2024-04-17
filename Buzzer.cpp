// Buzzer.cpp
#include "Buzzer.h"

Buzzer::Buzzer(int pin) {
  _buzzerPin = pin;
  pinMode(_buzzerPin, OUTPUT);
  _buzzerActive = false;
  _state = 0;
  _totalStartTime = millis();
}

void Buzzer::startBuzzer() {
  _totalStartTime = millis();  // Reset the timer whenever we start the buzzer
}

void Buzzer::updateBuzzer() {
  unsigned long currentMillis = millis();
  if (currentMillis - _totalStartTime >= 10000) {
    digitalWrite(_buzzerPin, LOW);
    return;
  }

  switch (_state) {
    case 0:
    case 2:
      if (!_buzzerActive) {
        digitalWrite(_buzzerPin, HIGH);
        _buzzerActive = true;
        _patternStartTime = currentMillis;
      } else if (currentMillis - _patternStartTime >= 100) {
        digitalWrite(_buzzerPin, LOW);
        _buzzerActive = false;
        _state++;
      }
      break;
    case 1:
      if (currentMillis - _patternStartTime >= 200) {
        _state++;
      }
      break;
    case 3:
      if (currentMillis - _patternStartTime >= 1000) {
        _state = 0;
      }
      break;
  }
}

void Buzzer::stopBuzzer() {
  digitalWrite(_buzzerPin, LOW);  // Immediately stop the buzzer
  _state = 0;  // Reset the state
}
