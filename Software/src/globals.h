#pragma once

#include <Arduino.h>
#define TWI_FREQ 400000L

#define PIN_ENCODER_A   3
#define PIN_ENCODER_B   13
#define PIN_ENCODER_BTN 12

#define ADDR_OLED_A     0x3C
#define ADDR_OLED_B     0x3D
#define NUM_OLEDS       2
#define UPDATE_TIME     250

#define debounceTime 25
const byte btns[] = { PIN_ENCODER_BTN };
const byte btnsSize = sizeof(btns) / sizeof(btns[0]);
bool btnState[btnsSize] = { 0 };
bool lastBtnState[btnsSize] = { 0 };

int8_t selectedItem = 0;
#define selectedItemMax 8

enum outputVoltages_t {
    VA6,
    VA12,
    VA5,
    VA72,
    VB6,
    VB12,
    VB5,
    VB72,
    outputVoltagesLength //crude hack to get enum size
};

bool outputState[outputVoltagesLength];
