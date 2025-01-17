#pragma once

#include <Arduino.h>

const uint8_t POWER_LED_PIN = D1;
const uint8_t POWER_BUTTON_PIN = D10;
const uint8_t RESET_BUTTON_PIN = D2;

extern bool *power_led_state;

void InitializePins();
