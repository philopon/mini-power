#include "./pins.hpp"
#include "./wifi.hpp"
#include "./server.hpp"
#include "./mdns.hpp"
#include "./fs.hpp"

void setup()
{
  Serial.begin(11520);

  IntializeLittleFs();
  InitializePins();
  InitializeWiFi();
  RegisterMDNS();

  BeginWebServer();
}

void loop()
{
  delay(1000);
}
