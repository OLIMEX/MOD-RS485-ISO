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

/* Make object with default address */
MOD_RS485_ISO rs;

void setup()
{
  Serial.begin(115200);
  while(!Serial);
}
void loop()
{
    Serial.println(F("MOD-RS485-ISO"));
    Serial.println(F("======================================================"));

    Serial.print(F("# Device ID: 0x"));
    Serial.println(rs.getID(), HEX);

    Serial.print(F("# Firmware: 0x"));
    Serial.println(rs.getFW(), HEX);

    /**
     * The device can operate in two modes:
     * - Pass mode - Signals on TX line pass straigth throw the device and
     * are transmitted to RS-485 line. The same apply to the RX.
     * - Bridge mode - TX and RX are disabled. Data can be send via I2C bus.
     *
     * Available values are:
     * Pass mode    - 0x00
     * Bridge mode  - 0x01
     */
    Serial.print(F("# Mode: 0x"));
    uint8_t mode = rs.getMode();
    Serial.println(mode, HEX);
    if(mode == MOD_RS485_ISO::PASS_MODE)
        Serial.println(F("# Working mode: Pass"));
    else
        Serial.println(F("# Working mode: Bridge"));

    /**
     * Direction is bitfield byte as follow:
     * - bit0 - RX enable
     * - bit1 - TX enable
     *
     * All other bits are don't care
     */
    Serial.print(F("# Control: 0x"));
    uint8_t direction = rs.getControl();
    Serial.println(direction, HEX);

    /* Check TX status */
    if(direction & MOD_RS485_ISO::TX_ENABLED)
        Serial.println(F("# TX Enabled: True"));
    else
        Serial.println(F("# TX Enabled: False"));
    /* Check RX status */
    if(direction & MOD_RS485_ISO::RX_ENABLED)
        Serial.println(F("# RX Enabled: True"));
    else
        Serial.println(F("# RX Enabled: False"));

    /**
     * When in brdige mode, you can select desired baudrate
     */
    Serial.print(F("# Baudrate: "));
    MOD_RS485_ISO::baudrate_t baud = rs.getBaudrate();
    switch(baud) {
        case MOD_RS485_ISO::UART_B50:       Serial.println(F("50"));        break;
        case MOD_RS485_ISO::UART_B75:       Serial.println(F("75"));        break;
        case MOD_RS485_ISO::UART_B110:      Serial.println(F("110"));       break;
        case MOD_RS485_ISO::UART_B134:      Serial.println(F("134"));       break;
        case MOD_RS485_ISO::UART_B150:      Serial.println(F("150"));       break;
        case MOD_RS485_ISO::UART_B300:      Serial.println(F("300"));       break;
        case MOD_RS485_ISO::UART_B600:      Serial.println(F("600"));       break;
        case MOD_RS485_ISO::UART_B1200:     Serial.println(F("1200"));      break;
        case MOD_RS485_ISO::UART_B1800:     Serial.println(F("1800"));      break;
        case MOD_RS485_ISO::UART_B2400:     Serial.println(F("2400"));      break;
        case MOD_RS485_ISO::UART_B4800:     Serial.println(F("4800"));      break;
        case MOD_RS485_ISO::UART_B7200:     Serial.println(F("7200"));      break;
        case MOD_RS485_ISO::UART_B9600:     Serial.println(F("9600"));      break;
        case MOD_RS485_ISO::UART_B14400:    Serial.println(F("14400"));     break;
        case MOD_RS485_ISO::UART_B19200:    Serial.println(F("19200"));     break;
        case MOD_RS485_ISO::UART_B38400:    Serial.println(F("38400"));     break;
        case MOD_RS485_ISO::UART_B57600:    Serial.println(F("57600"));     break;
        case MOD_RS485_ISO::UART_B76800:    Serial.println(F("76800"));     break;
        case MOD_RS485_ISO::UART_B115200:   Serial.println(F("115200"));    break;
        case MOD_RS485_ISO::UART_B128000:   Serial.println(F("128000"));    break;
        case MOD_RS485_ISO::UART_B230400:   Serial.println(F("230400"));    break;
        case MOD_RS485_ISO::UART_B500000:   Serial.println(F("500000"));    break;
        case MOD_RS485_ISO::UART_B576000:   Serial.println(F("576000"));    break;
        case MOD_RS485_ISO::UART_B1000000:  Serial.println(F("1000000"));   break;
    }

    Serial.println(F("======================================================"));

    while(1) {
    }
}
