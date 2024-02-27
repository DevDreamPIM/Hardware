// Put your libraries here, to import them:
#include "bluetooth.h"

// Put your external files here, to includes functions:
#include "constants.h"
#include "bluetooth.h"
#include "myo.h"
#include "wifi.h"
#include "httpRequest.h"
#include "PulseSensorManager.h"

// Put your global code here, to declare variables and other:
BluetoothSerial SerialBT;
PulseSensorManager pulseSensorManager(Constants::PULSE_INPUT_PIN,Constants::PULSE_THRESHOLD);

void sendDataToServer() {
  int bmp = pulseSensorManager.getBPM();
  int imu[] = {0, 0, 0, 0};//getImuData(); // 0 -> 3
  int emg[] = {0, 0, 0, 0, 0, 0, 0, 0};//getEmgData(); // 0 -> 8
  const char* user = Constants::USER;
  sendDataToServerHttp(user, imu, emg,bmp);
}

void setup() { // Put your setup code here, to run once:
  Serial.begin(115200);
 // setupBluetooth(SerialBT);
  setupWifi();

  pulseSensorManager.setup();

}

void loop() { // Put your main code here, to run repeatedly:
  handleBluetooth(SerialBT);
  //getTest();
  //myo_connect();
  // Pulse Sensor
  pulseSensorManager.update();
  sendDataToServer();

  
 

  delay(1000);
}
