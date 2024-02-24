#include "myo.h"

armband myo; // Myo BLE Armband
int imu_data_get[4];

//get data for POST Request
int* getImuData(){
  return imu_data_get;
}

// IMU Data
void imu_callback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
{
  myohw_imu_data_t *imu_data = (myohw_imu_data_t *)pData;
  imu_data_get[0] = imu_data->orientation.x;
  imu_data_get[1] = imu_data->orientation.y;
  imu_data_get[2] = imu_data->orientation.z;
  imu_data_get[3] = imu_data->orientation.w;
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
  //print_emg_sample(emg_data->sample2, myohw_num_emg_sensors);
}

void myo_connect()
{
  if (!myo.connected){
    Serial.println("Connecting to Myo device...");
    myo.connect();
    Serial.println(" - Connected to Myo device");
    delay(100);

    myo.set_myo_mode(myohw_emg_mode_send_emg,             // EMG mode
                   myohw_imu_mode_send_data,        // IMU mode
                   myohw_classifier_mode_disabled); // Classifier mode

    myo.imu_notification(TURN_ON)->registerForNotify(imu_callback);
    myo.emg_notification(TURN_ON)->registerForNotify(emg_callback);
  }
  
}
