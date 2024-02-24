#include "myo.h"

armband myo; // Myo BLE Armband
int imu_data_get[4];
int emg_data_get[8];

//get data for POST Request
int* getImuData(){
  return imu_data_get;
}

int* getEmgData(){
  return emg_data_get;
}


void imu_callback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
{
  myohw_imu_data_t *imu_data = (myohw_imu_data_t *)pData;
  imu_data_get[0] = imu_data->orientation.x;  //takes less space than for loop
  imu_data_get[1] = imu_data->orientation.y;
  imu_data_get[2] = imu_data->orientation.z;
  imu_data_get[3] = imu_data->orientation.w;
}

void emg_callback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
{
  myohw_emg_data_t *emg_data = (myohw_emg_data_t *)pData;
  emg_data_get[0] = emg_data->sample1[0];
  emg_data_get[1] = emg_data->sample1[1];
  emg_data_get[2] = emg_data->sample1[2];
  emg_data_get[3] = emg_data->sample1[3];
  emg_data_get[4] = emg_data->sample1[4];
  emg_data_get[5] = emg_data->sample1[5];
  emg_data_get[6] = emg_data->sample1[6];
  emg_data_get[7] = emg_data->sample1[7];
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
