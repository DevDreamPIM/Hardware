// Put your libraries here, to import them:
#include "BluetoothSerial.h"  // Nombre de caractères envoyés max est de 455 et prend environt 7 secondes à arriver dans flutter
#include <myo.h>

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
// Start Myo Gesture Control Code *************************************************************************
armband myo; // Myo BLE Armband

void myo_connect()
{
  Serial.println("Connecting to Myo device...");
  myo.connect();
  Serial.println(" - Connected to Myo device");
  delay(100);

  myo.set_myo_mode(myohw_emg_mode_none,             // EMG mode
                   myohw_imu_mode_send_data,        // IMU mode
                   myohw_classifier_mode_disabled); // Classifier mode
  // myo.set_myo_mode(myohw_emg_mode_send_emg,         // EMG mode
  //                  myohw_imu_mode_none,             // IMU mode
  //                  myohw_classifier_mode_disabled); // Classifier mode

  myo.imu_notification(TURN_ON)->registerForNotify(imu_callback);
  // myo.emg_notification(TURN_ON)->registerForNotify(emg_callback);
}

// IMU Data
void print_imu_orientation(myohw_imu_data_t *imu)
{
  Serial.print(imu->orientation.x);
  Serial.print("\t");
  Serial.print(imu->orientation.y);
  Serial.print("\t");
  Serial.print(imu->orientation.z);
  Serial.print("\t");
  Serial.print(imu->orientation.w);
  Serial.print("\t");
}

void imu_callback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
{
  myohw_imu_data_t *imu_data = (myohw_imu_data_t *)pData;
  print_imu_orientation(imu_data);
  Serial.println();
}

// EMG Data (Electromyography)
void print_emg_sample(int8_t *sample, size_t len)
{
  for (int i = 0; i < len; i++)
  {
    Serial.print(sample[i]);
    Serial.print("\t");
  }
  Serial.println();
}
void emg_callback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
{
  myohw_emg_data_t *emg_data = (myohw_emg_data_t *)pData;
  print_emg_sample(emg_data->sample1, myohw_num_emg_sensors);
  print_emg_sample(emg_data->sample2, myohw_num_emg_sensors);
}
// End Myo Gesture Control Code ***************************************************************************

void setup() { // Put your setup code here, to run once:  +++++++++++++++++++++++++++++++++++++++++++++++++++
  // Start Bluetooth Code ***********************************************************************************
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  // SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it to the phone with Bluetooth!\n", device_name.c_str());
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
  // End Bluetooth Code *************************************************************************************
  // Start Myo Gesture Control Code *************************************************************************
  if (!myo.connected)
  {
    myo_connect();
  }
  // End Myo Gesture Control Code ***************************************************************************
  
  delay(20);
}
