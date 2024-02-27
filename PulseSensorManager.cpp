// PulseSensorManager.cpp
#include "PulseSensorManager.h"

PulseSensorManager::PulseSensorManager(int pulsePin, int threshold) {
  this->pulseInput = pulsePin;
  this->threshold = threshold;
  this->lastBeatTime = 0;
  this->bpm = 0;
}

void PulseSensorManager::setup() {
  pulseSensor.analogInput(pulseInput);
  pulseSensor.setThreshold(threshold);
  pulseSensor.begin();
}

void PulseSensorManager::update() {
  if (pulseSensor.sawStartOfBeat()) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastBeatTime > debounceMillis) {
      bpm = pulseSensor.getBeatsPerMinute();
      lastBeatTime = currentMillis;
    }
  }
}

int PulseSensorManager::getBPM() {
  return bpm;
}
