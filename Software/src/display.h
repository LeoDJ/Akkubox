#pragma once

#include "globals.h"
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_HW_I2C dispA(U8G2_R0, U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_1_HW_I2C dispB(U8G2_R0, U8X8_PIN_NONE);

byte addr[] = {ADDR_OLED_A, ADDR_OLED_B};
U8G2* disp[] = {&dispA, &dispB};

const unsigned char* defaultFont = u8g2_font_logisoso16_tr;  //was u8g2_font_ncenB10_tr
const unsigned char* numberFont = u8g2_font_logisoso16_tn;



//debug function
/*
void dispL(byte x, byte y, const char* s) {
    byte i = 0;
    disp[i]->firstPage();
    do {
        disp[i]->setFont(defaultFont);
        disp[i]->drawStr(x, y, s);
    } while ( disp[i]->nextPage() );
}*/


const char* voltages[] = {"6", "12", "5", "7.2"};
byte horizontalGap[] = {0, 0, 6, 6};
byte arrowXPos[sizeof(horizontalGap)];
//#define marginLeft  4
byte marginLeft;
#define marginTop   16
#define gap 3
#define fontHeight  16

void initDisplay() {
    for(byte i = 0; i < NUM_OLEDS; i++) {
        disp[i]->setI2CAddress(addr[i] * 2);
        disp[i]->enableUTF8Print();
        disp[i]->begin();
        disp[i]->firstPage();
        do {
            disp[i]->setFont(defaultFont);
            //disp[i]->drawStr(0,24,"A\0B" + (i<<1));
            disp[i]->drawStr(16,24,"Akkubox");
        } while ( disp[i]->nextPage() );
    }

    
    disp[0]->setFont(numberFont);
    byte width = 0;
    for(byte v = 0; v < sizeof(horizontalGap); v++) {
        byte fontWidth = disp[0]->getStrWidth(voltages[v]);
        arrowXPos[v] = width + gap + horizontalGap[v] + fontWidth / 2;
        width += horizontalGap[v] + fontWidth + (gap*2);
    }

    marginLeft = (128 - width) / 2;

    for(byte i = 0; i < sizeof(arrowXPos); i++) 
        arrowXPos[i] += marginLeft;
}

void drawDisplay(byte i) {
    U8G2* d = disp[i];
    d->firstPage();
    do {
        if(i == selectedItem / (outputVoltagesLength / 2)) {
            //d->setFont(u8g2_font_unifont_t_symbols);
            d->setFont(defaultFont);
            d->setCursor(arrowXPos[selectedItem % (outputVoltagesLength / 2)] - 5, 12);
            d->print("v");
        }

        // alignment lines, remove later
        // d->drawLine(0, 0, 127, 63);
        // d->drawLine(127, 0, 0, 63);
        // d->drawLine(0, 0, 64, 63);
        // d->drawLine(127, 0, 64, 63);

        byte boxHeight = fontHeight + gap*2;
        d->setDrawColor(2); // set to XOR drawing
        d->setFont(numberFont);

        byte xOffset = marginLeft;
        for(byte v = 0; v < sizeof(horizontalGap); v++) {
            xOffset += horizontalGap[v];
            d->drawStr(xOffset + gap, marginTop + fontHeight + gap, voltages[v]);
            byte width = d->getStrWidth(voltages[v]) + gap*2;
            if (outputState[i*4 + v]) // select background based on output state
                d->drawBox(xOffset, marginTop, width, boxHeight);
            else        
                d->drawFrame(xOffset, marginTop, width, boxHeight);
            xOffset += width;
        }
        

    } while ( d->nextPage() );
}

void tickDisplay(bool onlyOneDisplay = false) {
    if(onlyOneDisplay) {
        drawDisplay(selectedItem / (outputVoltagesLength / 2));
    }
    for(byte i = 0; i < NUM_OLEDS; i++) {
        drawDisplay(i);
    }
}