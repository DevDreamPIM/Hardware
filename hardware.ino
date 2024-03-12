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

//String de récupération des données -> 10 min / 10 sec interval = 60 valeurs
String bpmStr= "bpm";
String emgStr= "emg";
String imuStr= "imu";
int lastIndex = 0;
long initialTime = millis();

bool SeizureMonitoringOn = true;

void dataProcessing() {
  //get sensor data for this instant
  int bpm = 210;// pulseSensorManager.getBPM();
  int imu = getImuData(); // axe w
  int emg = getEmgData(); //  8 en un

  //activer et desactiver la detection de crise
  if (SerialBT.available()) {
    String receivedString = SerialBT.readString();
    if (receivedString.equals("enableMonitoring")) {
        SeizureMonitoringOn = true;
    } else if (receivedString.equals("desableMonitoring")) {
        SeizureMonitoringOn = false;
    }
  }


  //ici ajouter la detection de crise en temps reel (avec variable Monitoring actif)
  if(bpm > 200 && emg > 35 && SeizureMonitoringOn){
    //déclencher le buzzer

    //déclancher l'alerte sur l'ecran

    //envoie de l'alerte crise par BLE avec le mot clef cri
    SerialBT.write((const uint8_t *)"cri", 3); // "cri" is 3 characters long
  }

  // Vérifier l'intervalle de 10 secondes
  long currentTime =  millis();
  if (currentTime - initialTime >= 1000) { // 10 secondes en millisecondes
    // Réinitialiser le temps initial
    initialTime = currentTime;
    if (lastIndex < 60) { // Vérifier si le tableau n'est pas plein
      bpmStr = bpmStr + "," + bpm;
      emgStr = emgStr + "," + emg;
      imuStr = imuStr + "," + imu;
      lastIndex++; // Mettre à jour l'index du dernier élément utilisé
    }
  }

  // ici, toutes les 10 minutes (index = 60),envoyer et vider les tableaux
  if (lastIndex == 60) {
    //envoyer les données par BLE
    SerialBT.write((const uint8_t*)bpmStr.c_str(), bpmStr.length());
    SerialBT.write((const uint8_t*)emgStr.c_str(), emgStr.length());
    SerialBT.write((const uint8_t*)imuStr.c_str(), imuStr.length());
    // Réinitialiser le temps initial et l'index du dernier élément utilisé
    initialTime = currentTime;
    lastIndex = 0;
    // Effacer le contenu des Strings en réinitialisant toutes les valeurs à une valeur par défaut
    bpmStr= "bpm";
    emgStr= "emg";
    imuStr= "imu";
  }
}

void setup() { // Put your setup code here, to run once:
  Serial.begin(115200);
  setupBluetooth(SerialBT);

  //pulseSensorManager.setup();

}

void loop() { // Put your main code here, to run repeatedly:
  handleBluetooth(SerialBT);
  myo_connect();
  //pulseSensorManager.update();

  dataProcessing();



  delay(40);
}
