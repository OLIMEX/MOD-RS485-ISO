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

/* MOD-RS485-ISO FIFO is limited to 64 bytes */
#define MAX_FIFO_SIZE   64

/* Make object with default address */
MOD_RS485_ISO rs;

/* Create data buffer with maximum FIFO size */
char data[MAX_FIFO_SIZE];

void setup()
{
  Serial.begin(115200);
  while(!Serial);

  /* Populate data buffer */
  sprintf(data, "Hello World from MOD-RS485-ISO!");

  /* Enable RX and TX */
  rs.setControl(MOD_RS485_ISO::RX_ENABLED | MOD_RS485_ISO::TX_ENABLED);
}

void loop()
{
    /* Change mode */
    Serial.println(F("Setting mode to bridge..."));
    rs.setMode(MOD_RS485_ISO::BRIDGE_MODE);

    /* Set baudrate */
    Serial.println(F("Setting baudrate to 9600..."));
    rs.setBaudrate(MOD_RS485_ISO::UART_B9600);

    /* Send data */
    Serial.print(F("Sending data: "));
    Serial.println(data);
    rs.sendData((uint8_t *)data, strlen(data));

    /**
     * Read responce
     *
     * If you close both A-Y, B-Z jumpers you'll create loopback
     */
    rs.readData((uint8_t *)data, MAX_FIFO_SIZE);
    Serial.print(F("Received data:"));
    Serial.println(data);

    while(1);
}
