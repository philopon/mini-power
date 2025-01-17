#include <Arduino.h>
#include "./pins.hpp"
#include "./server.hpp"

bool *power_led_state = new bool;

void PowerLedChanged()
{
    bool state = !digitalRead(POWER_LED_PIN);
    *power_led_state = state;

    SendPowerLedChangedFromISR(state);
}

void InitializePins()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    pinMode(POWER_BUTTON_PIN, OUTPUT);
    digitalWrite(POWER_BUTTON_PIN, LOW);

    pinMode(RESET_BUTTON_PIN, OUTPUT);
    digitalWrite(RESET_BUTTON_PIN, LOW);

    pinMode(POWER_LED_PIN, INPUT_PULLUP);
    *power_led_state = !digitalRead(POWER_LED_PIN);
    attachInterrupt(POWER_LED_PIN, PowerLedChanged, CHANGE);
}
