#pragma once

#include <ESPAsyncWebServer.h>

void BeginWebServer();

bool SendPowerLedChangedFromISR(bool status);
