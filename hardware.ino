// Put your libraries here, to import them:
#include "bluetooth.h"

// Put your external files here, to includes functions:
#include "bluetooth.h"
#include "myo.h"
#include "wifi.h"
#include "httpRequest.h"


// Put your global code here, to declare variables and other:
BluetoothSerial SerialBT;

void sendDataToServer() {
  int* imu = getImuData(); // 0 -> 3
  int* emg = getEmgData(); // 0 -> 8
  String user = "609f1519c33d2d001d45e777";
  sendDataToServerHttp(user, imu, emg);
}

void setup() { // Put your setup code here, to run once:
  Serial.begin(115200);
  setupBluetooth(SerialBT);
  setupWifi();

}

void loop() { // Put your main code here, to run repeatedly:
  handleBluetooth(SerialBT);
  //getTest();
  myo_connect();

  sendDataToServer();

  delay(40);
}
