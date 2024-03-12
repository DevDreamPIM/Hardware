// Put your libraries here, to import them:
#include "bluetooth.h"

// Put your external files here, to includes functions:
#include "constants.h"
#include "bluetooth.h"
#include "myo.h"
#include "PulseSensorManager.h"

// Put your global code here, to declare variables and other:
BluetoothSerial SerialBT;
//PulseSensorManager pulseSensorManager(Constants::PULSE_INPUT_PIN,Constants::PULSE_THRESHOLD);

void sendDataToPhone() {
  int bmp = 70;// pulseSensorManager.getBPM();
  int* imu = getImuData(); // 0 -> 3
  int* emg = getEmgData(); // 0 -> 8
}

void setup() { // Put your setup code here, to run once:
  Serial.begin(115200);
  setupBluetooth(SerialBT);

  //pulseSensorManager.setup();

}

void loop() { // Put your main code here, to run repeatedly:
  handleBluetooth(SerialBT);
  myo_connect();
  // Pulse Sensor
  //pulseSensorManager.update();

  
 

  delay(40);
}
