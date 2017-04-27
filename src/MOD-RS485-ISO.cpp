/*
 * RS485ISO.cpp
 *
 * Copyright 2013 OLIMEX LTD/Stefan Mavrodiev <support@olimex.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */


#include <Arduino.h>
#include <Wire.h>
#include "MOD-RS485-ISO.h"


uint8_t MOD_RS485_ISO::TX_ENABLED   = (1 << 1);
uint8_t MOD_RS485_ISO::TX_DISABLED  = (0 << 1);
uint8_t MOD_RS485_ISO::RX_ENABLED   = (1 << 0);
uint8_t MOD_RS485_ISO::RX_DISABLED  = (0 << 0);

uint8_t MOD_RS485_ISO::PASS_MODE    = 0x00;
uint8_t MOD_RS485_ISO::BRIDGE_MODE  = 0x01;

/**
 * @brief MOD_RS485_ISO
 * Default constructor
 *
 * @param address           I2C address if default is not used
 */
MOD_RS485_ISO::MOD_RS485_ISO(uint8_t address) :
    __address(address)
{

}

/**
 * @brief MOD_RS485_ISO::getID
 * Get device ID
 */
uint8_t MOD_RS485_ISO::getID(void)
{
    return __readRegister(REGISTER_ID);
}

/**
 * @brief MOD_RS485_ISO::getFW
 * Get firmware revision
 *
 * @return Firmware revision number
 */
uint8_t MOD_RS485_ISO::getFW(void)
{
    return __readRegister(REGISTER_FW);
}

/**
 * @brief MOD_RS485_ISO::setControl
 * Enable TX/RX data flow
 *
 * @param direction         Bitfield describing data direction
 */
void MOD_RS485_ISO::setControl(uint8_t direction)
{
    __writeRegister(REGISTER_CTRL, direction);
}

/**
 * @brief MOD_RS485_ISO::getControl
 * Read current data direction control
 *
 * @return              Bitflield byte
 */
uint8_t MOD_RS485_ISO::getControl(void)
{
    return __readRegister(REGISTER_CTRL);
}

/**
 * @brief MOD_RS485_ISO::setMode
 * Set operating mode
 *
 * @param mode          One of the following:
 *  0x00    -   Pass mode
 *  0x01    -   Bridge mode
 */
void MOD_RS485_ISO::setMode(uint8_t mode)
{
    __writeRegister(REGISTER_MODE, mode);
}

/**
 * @brief MOD_RS485_ISO::getMode
 * Get current operating mode
 *
 * @return      Current operating mode
 */
uint8_t MOD_RS485_ISO::getMode()
{
    return __readRegister(REGISTER_MODE);
}

/**
 * @brief MOD_RS485_ISO::setBaudrate
 * Set RS-485 baudrate. Only usable when in bridge mode
 *
 * @param baud      One of available values
 * @see enum baudrate
 */
void MOD_RS485_ISO::setBaudrate(baudrate_t baud)
{
    __writeRegister(REGISTER_BR, (uint8_t)baud);
}

/**
 * @brief MOD_RS485_ISO::getBaudrate
 * Get current set baudrate
 *
 * @return          Current set baudrate
 */
MOD_RS485_ISO::baudrate_t MOD_RS485_ISO::getBaudrate(void)
{
    return __readRegister(REGISTER_BR);
}

/**
 * @brief MOD_RS485_ISO::sendData
 * Send data to FIFO buffer
 *
 * @param data          Pointer to data buffer
 * @param length        Number of bytes to write
 */
void MOD_RS485_ISO::sendData(uint8_t *data, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++) {
        __writeRegister(REGISTER_TX, data[i]);
    }

}

/**
 * @brief MOD_RS485_ISO::readData
 * Read data from FIFO buffer
 *
 * @param data          Pointer to data buffer
 * @param length        Number of byte to read
 */
void MOD_RS485_ISO::readData(uint8_t *data, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++) {
        data[i] = __readRegister(REGISTER_RX);
    }
}

/**
 * @breif MOD_RS485_ISO::setAddress
 * Set new I2C address
 *
 * @param address       New address
 */
void MOD_RS485_ISO::setAddress(uint8_t address)
{
    /* Check if new address is valid one */
    if (address > 0x77 || address < 0x03)
        return;

    __writeRegister(REGISTER_ADDR, address);
}

/**
 * @brief MOD_RS485_ISO::__writeRegister
 * Write single byte to memory
 *
 * @param reg               Register address
 * @param data              Data to be written
 */
void MOD_RS485_ISO::__writeRegister(uint8_t reg, uint8_t data)
{
    Wire.begin();
    Wire.beginTransmission(__address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

/**
 * @brief MOD_RS485_ISO::__readRegister
 * Read single byte from registers
 *
 * @param reg               Register address
 * @return                  Value of the register
 */
uint8_t MOD_RS485_ISO::__readRegister(uint8_t reg)
{
    Wire.begin();
    Wire.beginTransmission(__address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom((int)__address, 1);
    return (uint8_t)Wire.read();

}
