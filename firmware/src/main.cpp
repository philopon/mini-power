#include "./pins.hpp"
#include "./wifi.hpp"
#include "./server.hpp"
#include "./mdns.hpp"

void setup()
{
  Serial.begin(11520);

  InitializePins();
  InitializeWiFi();
  RegisterMDNS();

  BeginWebServer();
}

void loop()
{
}
