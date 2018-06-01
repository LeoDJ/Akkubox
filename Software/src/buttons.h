#pragma once

#include "globals.h"

void initButtons() {
    pinMode(PIN_ENCODER_BTN, INPUT_PULLUP);
}


void buttonPressed(byte id) {
    if(id == 0) {
        switch(selectedItem) {
            case VA6:
                if(outputState[VA12]) {
                    outputState[VA12] = false;
                    outputState[VA6] = true;
                    // TODO: switch really
                }
                else {
                    outputState[VA6] = !outputState[VA6];
                }
            break;
            case VA12:
                if(outputState[VA6]) {
                    outputState[VA6] = false;
                    outputState[VA12] = true;
                    // TODO: switch really
                }
                else {
                    outputState[VA12] = !outputState[VA12];
                }
            break;
            case VB6:
                if(outputState[VB12]) {
                    outputState[VB12] = false;
                    outputState[VB6] = true;
                    // TODO: switch really
                }
                else {
                    outputState[VB6] = !outputState[VB6];
                }
            break;
            case VB12:
                if(outputState[VB6]) {
                    outputState[VB6] = false;
                    outputState[VB12] = true;
                    // TODO: switch really
                }
                else {
                    outputState[VB12] = !outputState[VB12];
                }
            break;
            case VA5:
            case VB5:
                outputState[VA5] = !outputState[VA5];
                outputState[VB5] = !outputState[VB5];
            break;
            case VA72:
            case VB72:
                outputState[VA72] = !outputState[VA72];
                outputState[VB72] = !outputState[VB72];
            break;
        }
    }
}


unsigned long lastBtnPress = 0;
void tickButtons()
{
    for (byte i = 0; i < btnsSize; i++) {
        bool state = digitalRead(btns[i]);
        Serial.println(state);
        if (state != lastBtnState[i] && (millis() - lastBtnPress) > debounceTime) {
            if (state == false) { //buttons are active low
                buttonPressed(i);
            } else if(state == true) {
                //buttonReleased() not implemented yet, maybe long press functionality
            }
            lastBtnPress = millis();
        }
        lastBtnState[i] = state;
    }
}