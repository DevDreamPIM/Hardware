#include "httpRequest.h"

unsigned long lastTime = 0;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 500; // 500 ms

void sendDataToServerHttp(String user, int* imu, int* emg,int bmp){
if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, Constants::serverName);
      
      http.addHeader("Content-Type", "application/json");

      // Construct JSON data
            String jsonPayload = "{\"user\":\"" + user + "\",\"imu\":[" 
                                + String(imu[0]) + "," + String(imu[1]) + "," 
                                + String(imu[2]) + "," + String(imu[3]) + "],"
                                + "\"emg\":[" 
                                + String(emg[0]) + "," + String(emg[1]) + "," 
                                + String(emg[2]) + "," + String(emg[3]) + ","
                                + String(emg[4]) + "," + String(emg[5]) + "," 
                                + String(emg[6]) + "," + String(emg[7]) + "],"
                                 + "\"bmp\":" + String(bmp) + "}";

      int httpResponseCode = http.POST(jsonPayload);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
