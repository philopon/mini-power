#include <ESPmDNS.h>
#include "./config.hpp"

void RegisterMDNS()
{
    if (!MDNS.begin(MDNS_NAME))
    {
        Serial.println("Cannot register mDNS.");
        return;
    }
}
