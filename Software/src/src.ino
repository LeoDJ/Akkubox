#include "globals.h"
#include <Arduino.h>
#include "display.h"
#include "ctrl_encoder.h"
#include "buttons.h"

//see globals.h

void setup() {
    Serial.begin(115200);
    initDisplay();
    initButtons();
}

unsigned long lastUpdateTime = 0;

void loop() {
    tickEncoder();
    tickButtons();
    if(millis() - lastUpdateTime >= UPDATE_TIME) {
        lastUpdateTime = millis();
        tickDisplay();
    }
}