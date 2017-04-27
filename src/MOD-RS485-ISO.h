/*
 * MOD-RS485-ISO.h
 *
 * Copyright 2017 OLIMEX Ltd. <support@olimex.com>
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

#ifndef MOD_RS485_ISO_H
#define MOD_RS485_ISO_H

#include <inttypes.h>

/* Define read-only registers */
#define REGISTER_ID          0x20
#define REGISTER_FW          0x21
/* Define read/write registers */
#define REGISTER_ADDR       0x22
#define REGISTER_MODE       0x23
#define REGISTER_CTRL       0x24
#define REGISTER_BR         0x25

#define REGISTER_TX         0x26
#define REGISTER_RX         0x27


class MOD_RS485_ISO
{

public:
    /* Define available baudrates */
    typedef enum {
        UART_B50 = 0,
        UART_B75,
        UART_B110,
        UART_B134,
        UART_B150,
        UART_B300,
        UART_B600,
        UART_B1200,
        UART_B1800,
        UART_B2400,
        UART_B4800,
        UART_B7200,
        UART_B9600,
        UART_B14400,
        UART_B19200,
        UART_B38400,
        UART_B57600,
        UART_B76800,
        UART_B115200,
        UART_B128000,
        UART_B230400,
        UART_B500000,
        UART_B576000,
        UART_B1000000
    } baudrate_t ;

    MOD_RS485_ISO(uint8_t address = 0x22);

    uint8_t getID(void);
    uint8_t getFW(void);

    void setAddress(uint8_t address);

    void setControl(uint8_t direction);
    uint8_t getControl(void);

    void setMode(uint8_t mode);
    uint8_t getMode(void);

    void setBaudrate(baudrate_t baud);
    baudrate_t getBaudrate(void);

    void sendData(uint8_t *data, uint8_t length);
    void readData(uint8_t *data, uint8_t length);


    static uint8_t TX_ENABLED;
    static uint8_t TX_DISABLED;
    static uint8_t RX_ENABLED;
    static uint8_t RX_DISABLED;

    static uint8_t PASS_MODE;
    static uint8_t BRIDGE_MODE;

private:
    uint8_t __address;

    void __writeRegister(uint8_t register, uint8_t data);
    uint8_t __readRegister(uint8_t register);

};
#endif
