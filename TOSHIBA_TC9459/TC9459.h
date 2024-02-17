/*
  The MIT License (MIT)

  Copyright (c) 2024 Jerry Long

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
#ifndef INCLUDED_TOSHIBA_TC9459
#define INCLUDED_TOSHIBA_TC9459

#include <Arduino.h>

class TC9459
{
public:
    //contextual data types
    typedef uint8_t pin_t;
    typedef uint8_t volume_t;
    typedef uint16_t data_t;
    typedef uint8_t loudness_address_t

    //specify a connection over an address using 3 SPI pins.
    TC9459(loudness_address_t loudness_chip_address);

    //set the SPI pins in their correct states
    void begin();

    //set the volume
    //audio signal goes from [-89, 0]dB
    //input data goes from [89, 0]
    //control data goes from [0b1001101, 0b0000000]
    void setVolume(volume_t left, volume_t right);

    void mute();


private:
    // for multiple chips on the same bus line.
    // CS1   CS2   C1  C2  C3  C4
    // L     L     0   0   0   1
    // H     L     1   0   0   1
    // L     H     0   1   0   1
    // H     H     1   1   0   1
    address_t chip_address;
    data_t states;
};
#endif // INCLUDED_TOSHIBA_TC9459