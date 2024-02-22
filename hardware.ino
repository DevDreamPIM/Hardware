// Put your libraries here, to import them:
#include "bluetooth.h"

// Put your external files here, to includes functions:
#include "bluetooth.h"
#include "myo.h"

// Put your global code here, to declare variables and other:
BluetoothSerial SerialBT;

void setup() { // Put your setup code here, to run once:
  Serial.begin(115200);
  setupBluetooth(SerialBT);

}

void loop() { // Put your main code here, to run repeatedly:
  handleBluetooth(SerialBT);
  myo_connect();

  delay(40);
}
