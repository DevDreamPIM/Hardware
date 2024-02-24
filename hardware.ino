// Put your libraries here, to import them:
#include "bluetooth.h"

// Put your external files here, to includes functions:
#include "bluetooth.h"
#include "myo.h"
#include "wifi.h"
#include "httpRequest.h"


// Put your global code here, to declare variables and other:
BluetoothSerial SerialBT;

void setup() { // Put your setup code here, to run once:
  Serial.begin(115200);
  setupBluetooth(SerialBT);
  setupWifi();

}

void loop() { // Put your main code here, to run repeatedly:
  handleBluetooth(SerialBT);
  //getTest();
  myo_connect();


  int* imu = getImuData();
  Serial.println(imu[0]);
  Serial.print(imu[1]);
  Serial.print(imu[2]);
  Serial.print(imu[3]);


  delay(40);
}
