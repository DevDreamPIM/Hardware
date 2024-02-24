#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "constants.h"
#include <HTTPClient.h>

void sendDataToServerHttp(String user, int* imu, int* emg);

#endif