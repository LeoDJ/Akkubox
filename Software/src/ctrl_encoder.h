#pragma once

#include "globals.h"
#include <Encoder.h>
#include "display.h"

Encoder enc(PIN_ENCODER_A, PIN_ENCODER_B);

void encMove(bool direction) {
    selectedItem += direction ? 1 : -1;

    if(selectedItem < 0)
        selectedItem = selectedItemMax - 1;
    else if (selectedItem >= selectedItemMax)
        selectedItem = 0;
}

long encPos, lastEncPos = 0;
void tickEncoder() {
    /*String d = String(digitalRead(PIN_ENCODER_A)) + " " + String(digitalRead(PIN_ENCODER_B)) + " " + String(enc.read());
    dispL(0, 48, d.c_str());
    Serial.println(d);*/

    encPos = enc.read();
    bool triggered = false;
    while (encPos - lastEncPos > 3 || encPos - lastEncPos < -3) { //process multiple turns at once
        triggered = true;
        int diff = encPos - lastEncPos;
        encMove(diff > 0);
        lastEncPos += (diff < 0) ? -4 : 4; //only add/subtract 4 as to run the inc/dec function the correct number of times
    }

    if(triggered) {
        tickDisplay(true); //update only relevant display
    }

}