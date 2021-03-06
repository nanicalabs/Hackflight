/*
   Sketch for FURYF4 board with DSMX receiver

   Copyright (c) 2019 Simon D. Levy

   This file is part of Hackflight.

   Hackflight is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Hackflight is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with Hackflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <hackflight.hpp>
#include <mixers/quadxcf.hpp>
#include <pidcontrollers/level.hpp>
#include <boards/stm32f/furyf4.hpp>
#include <receivers/stm32f/dsmx.hpp>

constexpr uint8_t CHANNEL_MAP[6] = {0, 1, 2, 3, 6, 4};

static hf::Hackflight h;

extern "C" {

#include "time.h"

    void setup(void)
    {
        hf::Rate * ratePid = new hf::Rate(
                0.05f, // Gyro cyclic P
                0.00f, // Gyro cyclic I
                0.00f, // Gyro cyclic D
                0.10f, // Gyro yaw P
                0.01f, // Gyro yaw I
                8.58); // Demands to rate

        // Create a DSMX Receiver object
        DSMX_Receiver * rc = new DSMX_Receiver(UARTDEV_3, CHANNEL_MAP);

        // Create an OmnibusF3 Board object
        FuryF4 * board = new FuryF4();

        h.init(board, rc, new hf::MixerQuadXCF(), ratePid);
    }

    void loop(void)
    {
        h.update();
    }

} // extern "C"
