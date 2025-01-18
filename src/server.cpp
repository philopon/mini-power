#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <Ticker.h>
#include <LittleFS.h>

#include "./wifi.hpp"
#include "./pins.hpp"
#include "./server.hpp"
#include "./svelteesp32.h"
#include "./fs.hpp"

AsyncWebServer server(80);

// messaging
TaskHandle_t taskHandle;
QueueHandle_t eventQueue;
AsyncEventSource events("/events");

bool SendPowerLedChangedFromISR(bool status)
{
    return xQueueSendFromISR(eventQueue, &status, 0) == pdTRUE;
}

// routes
void GetStatus(AsyncWebServerRequest *request)
{
    PushLog("GET /api/status");
    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonObject root = response->getRoot();
    root["status"] = *power_led_state;
    root["mac"] = MAC_ADDRESS;
    root["ip"] = LOCAL_IP;

    response->setLength();
    request->send(response);
}

Ticker power_button_ticker;

void PostPower(AsyncWebServerRequest *request)
{
    PushLog("POST /api/power");

    digitalWrite(POWER_BUTTON_PIN, HIGH);
    power_button_ticker.once_ms(500, []()
                                { digitalWrite(POWER_BUTTON_PIN, LOW); });
    request->send(200, "application/json", "{\"ok\": true}");
}

void (*resetFunc)(void) = 0;

void PostResetBoard(AsyncWebServerRequest *request)
{
    PushLog("POST /api/reset_board");

    resetFunc();
    request->send(200, "application/json", "{\"ok\": true}");
}

// task
void ResendMessageTask(void *pvParameters)
{
    bool status;

    while (true)
    {
        if (xQueueReceive(eventQueue, &status, 1000) == pdTRUE)
        {
            PushLog("SEND MESSAGE");
            JsonDocument doc;
            doc["status"] = status;

            String message;
            serializeJson(doc, message);

            events.send(message, "status", millis());
        }
    }
}

void BeginWebServer()
{
    eventQueue = xQueueCreate(8, sizeof(bool));

    xTaskCreateUniversal(ResendMessageTask, "ResendMessage", 8192, NULL, 1, &taskHandle, CONFIG_ARDUINO_RUNNING_CORE);

    server.addHandler(&events);

    server.on("/api/status", HTTP_GET, GetStatus);
    server.on("/api/power", HTTP_POST, PostPower);
    server.on("/api/reset_board", HTTP_POST, PostResetBoard);
    server.serveStatic("/api/log", LittleFS, LOG_FILE_PATH);
    initSvelteStaticFiles(&server);

    server.begin();
}
