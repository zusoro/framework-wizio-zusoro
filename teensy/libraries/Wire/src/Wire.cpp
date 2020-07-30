/*
    Created on: 01.01.2019
    Author: Georgi Angelov
        http://www.wizio.eu/
        https://github.com/Wiz-IO    

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
 */

extern "C"
{
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
}

#include "Wire.h"
#include <Arduino.h>

TwoWire::TwoWire(uint8_t bus_num):
    last_error(0)
{
}

TwoWire::~TwoWire()
{
}

bool TwoWire::begin(int sdaPin, int sclPin, uint32_t frequency)
{

    return true;
}

void TwoWire::setTimeOut(uint16_t timeOutMillis)
{
}

uint16_t TwoWire::getTimeOut()
{
    return 0;
}

void TwoWire::setClock(uint32_t frequency)
{
}

//size_t TwoWire::getClock() { return 0; }

int TwoWire::writeTransmission(uint16_t address, uint8_t *buff, uint16_t size, bool sendStop)
{
    return last_error;
}

int TwoWire::readTransmission(uint16_t address, uint8_t *buff, uint16_t size, bool sendStop, uint32_t *readCount)
{
    return last_error;
}

void TwoWire::beginTransmission(uint16_t address)
{
    last_error = 0;
}

/*stickbreaker isr
 */
uint8_t TwoWire::endTransmission(bool sendStop) // Assumes Wire.beginTransaction(), Wire.write()
{
    return last_error;
}


size_t TwoWire::write(uint8_t data)
{
    return 0;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
    return quantity;
}

int TwoWire::available(void)
{
    return 0;
}

int TwoWire::read(void)
{
    return 0;
}

int TwoWire::peek(void)
{
    return 0;
}

void TwoWire::flush(void)
{
}

uint8_t TwoWire::receive(void) {
		return last_error;
	}


uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop) {
		return last_error;
	}

void TwoWire::send(uint8_t b) {
		write(b);
	}
    
void TwoWire::beginTransmission(int address)
{
    beginTransmission(static_cast<uint16_t>(address));
}

void TwoWire::beginTransmission(uint8_t address)
{
    beginTransmission(static_cast<uint16_t>(address));
}

uint8_t TwoWire::endTransmission(void)
{
    return endTransmission(true);
}

/* stickbreaker Nov2017 better error reporting
 */
uint8_t TwoWire::lastError()
{
    return (uint8_t)last_error;
}

const char ERRORTEXT[] =
    "OK\0"
    "DEVICE\0"
    "ACK\0"
    "TIMEOUT\0"
    "BUS\0"
    "BUSY\0"
    "MEMORY\0"
    "CONTINUE\0"
    "NO_BEGIN\0"
    "\0";

char *TwoWire::getErrorText(uint8_t err)
{
    uint8_t t = 0;
    bool found = false;
    char *message = (char *)&ERRORTEXT;

    while (!found && message[0])
    {
        found = t == err;
        if (!found)
        {
            message = message + strlen(message) + 1;
            t++;
        }
    }
    if (!found)
    {
        return NULL;
    }
    else
    {
        return message;
    }
}



TwoWire Wire = TwoWire(0);
TwoWire Wire1 = TwoWire(1);