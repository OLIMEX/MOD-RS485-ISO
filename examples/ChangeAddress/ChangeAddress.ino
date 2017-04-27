// Copyright (c) 2017 Olimex Ltd.
//
// GNU GENERAL PUBLIC LICENSE
//    Version 3, 29 June 2007
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <MOD-RS485-ISO.h>

#define DEFAULT_ADDRESS     0x22
#define NEW_ADDRESS         0x33

/* MOD-RS485-ISO has ID 0x25 */
#define DEFAULT_ID          0x25

#define BUTTON              2

/**
 * Check if device at address is MOD-RS485-ISO
 */
bool isAlive(uint8_t address)
{
    MOD_RS485_ISO device(address);

    return (device.getID() == DEFAULT_ID);
}

void waitButton()
{
    /* Wait button press */
    while(digitalRead(BUTTON)) {
        delay(10);
    }

    /* Wait button release */
    while(!digitalRead(BUTTON)) {
        delay(10);
    }
}

void setup()
{
    Serial.begin(115200);
    while(!Serial);

    pinMode(BUTTON, INPUT);
}
void loop()
{
    MOD_RS485_ISO rs(DEFAULT_ADDRESS);
    Serial.print(F("Searching MOD-RS485-ISO on address: 0x"));
    Serial.println(DEFAULT_ADDRESS, HEX);

    /* Check device is alive */
    if (!isAlive(DEFAULT_ADDRESS)) {
        Serial.println(F("Couldn't find device!"));
        Serial.println(F("To reset to factory settings, close PROG jumper and reset the module."));
        while(1);
    } else {
        Serial.println(F("Device found."));
    }

    /* Change address */
    Serial.println(F("\nTo change device address PROG jumper should be closed."));
    Serial.println(F("Press BUT to continue..."));
    waitButton();
    rs.setAddress(NEW_ADDRESS);
    Serial.print(F("Searching MOD-RS485-ISO on address: 0x"));
    Serial.println(NEW_ADDRESS, HEX);
    if(!isAlive(NEW_ADDRESS)) {
        Serial.println(F("Couldn't change device address!"));
        while(1);
    } else {
        Serial.println(F("Device address changed successfully."));
    }

    /* Now revert to factory settings */
    Serial.println(F("\nTo restore default settings press RST button while PROG jumper is closed."));
    Serial.println(F("Press BUT to continue..."));
    waitButton();

    Serial.print(F("Searching MOD-RS485-ISO on address: 0x"));
    Serial.println(DEFAULT_ADDRESS, HEX);
    if (!isAlive(DEFAULT_ADDRESS)) {
        Serial.println(F("Couldn't find device on default address!"));
        while(1);
    } else {
        Serial.println(F("Device found."));
    }





    while(1);
}
