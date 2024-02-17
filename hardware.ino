// Put your libraries here, to import them:
#include "BluetoothSerial.h"

// Put your global code here, to declare variables and other:
// Start Bluetooth Code ***********************************************************************************
String device_name = "DevDream-SmartWatch";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
  #error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
// End Bluetooth Code *************************************************************************************

void setup() { // Put your setup code here, to run once:  +++++++++++++++++++++++++++++++++++++++++++++++++++
  // Start Bluetooth Code ***********************************************************************************
  Serial.begin(115200);
    SerialBT.begin(device_name); //Bluetooth device name
    // SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
    Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  // End Bluetooth Code *************************************************************************************

}

void loop() { // Put your main code here, to run repeatedly:  +++++++++++++++++++++++++++++++++++++++++++++++
  // Start Bluetooth Code ***********************************************************************************
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
  // End Bluetooth Code *************************************************************************************

}
