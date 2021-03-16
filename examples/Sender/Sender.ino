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
// 
// Tested with 2 ESP32-EVB Rev.I + 2 MOD-RS485-ISO connected to the UEXT
// The 2 MOD-RS485-ISO modules are connected between each other:
// A to A; B to B; GND_ISO to GND_ISO
// and the AB jumpers are closed on both modules
// 
// One of the ESP32-EVB board is programmed with Sender sketch
// the other ESP32-EVB with Receiver sketch (both sketches are part of the library examples)
//
// Upon sending character from the Sender the Receiver will announce it
//
// Known bug: Sometimes there is an issue with the transfer resulting in a loss of data

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

  /* Enable TX */
  rs.setControl(TX_ENABLED);
  
  /* Change mode */
  Serial.println("Setting mode to bridge...");
  rs.setMode(BRIDGE_MODE);

  /* Set baudrate */
  Serial.println("Setting baudrate to 9600...");
  rs.setBaudrate(UART_B9600);
}

int send_index=0;
void loop()
{
  while (Serial.available () > 0)
  {
    data[send_index++] = Serial.read ();
    delay (10);
  }
  if (send_index > 0)
  {
    data[send_index] = 0;
    Serial.print ("Sending data: ");
    Serial.println (data);
    rs.sendData((uint8_t *)&data, strlen(data));
    send_index = 0;
  }
}
