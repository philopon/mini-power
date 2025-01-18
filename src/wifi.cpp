#include <WiFi.h>
#include "./wifi.hpp"
#include "./config.hpp"

String MAC_ADDRESS;
IPAddress LOCAL_IP;

void OnWiFiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("Disconnected from WiFi access point");
    Serial.print("WiFi lost connection. Reason: ");
    Serial.println(info.wifi_sta_disconnected.reason);
    Serial.println("Trying to Reconnect");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void OnWiFiGotIp(WiFiEvent_t event, WiFiEventInfo_t info)
{
    LOCAL_IP = WiFi.localIP();
    Serial.println(LOCAL_IP);
}

void InitializeWiFi()
{
    WiFi.mode(WIFI_STA);

    WiFi.onEvent(OnWiFiDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
    WiFi.onEvent(OnWiFiGotIp, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);

    WiFi.disconnect(true);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi ..");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(800);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
        digitalWrite(LED_BUILTIN, HIGH);
    }
    Serial.println();
    MAC_ADDRESS = WiFi.macAddress();
    digitalWrite(LED_BUILTIN, HIGH);
}
