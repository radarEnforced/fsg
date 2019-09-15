/****************************************************************************//*
 * Copyright (C) 2019 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef SIM_DEFS_H
#define SIM_DEFS_H

////////////////////////////////////////////////////////////////////////////////

#ifdef __ANDROID__
#   define SIM_DATA_PATH "/sdcard/Download/data/"
#else
#   define SIM_DATA_PATH "data/"
#endif

////////////////////////////////////////////////////////////////////////////////

#define SIM_FAILURE 0
#define SIM_SUCCESS 1

////////////////////////////////////////////////////////////////////////////////

#define SIM_TIME_STEP_MIN 0.001
#define SIM_TIME_STEP_MAX 0.200

#define SIM_END_DELAY 5.0f

////////////////////////////////////////////////////////////////////////////////

#define SIM_ENTITIES_MAX 2048

////////////////////////////////////////////////////////////////////////////////

#define SIM_GRAVITY_ACC 9.81f

////////////////////////////////////////////////////////////////////////////////

#define SIM_AIRCRAFT_MAX_PHI ( 72.0 * M_PI / 180.0 )
#define SIM_AIRCRAFT_MAX_THT ( 20.0 * M_PI / 180.0 )

////////////////////////////////////////////////////////////////////////////////

#define SIM_DEPTH_SORTED_BIN_WORLD  0
#define SIM_DEPTH_SORTED_BIN_SKY    1
#define SIM_DEPTH_SORTED_BIN_OTHER  2
#define SIM_DEPTH_SORTED_BIN_TRAIL  2
#define SIM_DEPTH_SORTED_BIN_HUD    3
#define SIM_DEPTH_SORTED_BIN_MSG    5 /* This is intentional! */

////////////////////////////////////////////////////////////////////////////////

#define SIM_SKYDOME_RAD 8000.0f

////////////////////////////////////////////////////////////////////////////////

#define SIM_LIGHT_SUN_NUM 0

////////////////////////////////////////////////////////////////////////////////

#define SIM_MSG_LEN 2048

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_DEFS_H
