/*
  The MIT License (MIT)

  Copyright (c) 2016 Jerry Long

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "TC9459.h"
#include <SPI.h>

typedef TC9459 Self;

//pass through some types into global scope
using data_t = Self::data_t;
using volume_t = Self::volume_t;

// pin number of SPI CS pin
static const int s_slave_select_pin = 10;

static const SPISettings s_TC9459_spi_settings(250000, LSBFIRST, SPI_MODE0);

Self::TC9459(loudness_address_t chip_address):
      chip_address(chip_address & 0b11110000),
      states(0)
{}

void Self:: turnOnLoudness(bool enabled)
{
    //1 is enabled, 0 is disabled
    if(enabled)
    {
        chip_address = chip_address | 0b00000001 ;
    }
    else
    {
        chip_address = chip_address & 0b11110000 ;
    }
}

void Self::mute()
{

}

void Self::begin()
{
    pinMode(s_slave_select_pin, OUTPUT);
    digitalWrite(s_slave_select_pin, HIGH);
    SPI.begin();    
}

void Self::setVolume(volume_t lch, volume_t rch)
{
    SPI.beginTransaction(s_TC9459_spi_settings);
    digitalWrite(s_slave_select_pin, LOW);

    SPI.transfer(lch);
    SPI.transfer(rch);
    SPI.transfer(chip_address);

    digitalWrite(s_slave_select_pin, HIGH);
    SPI.endTransaction();
}

