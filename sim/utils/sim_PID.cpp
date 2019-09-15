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

#include <sim/utils/sim_PID.h>

#include <algorithm>

#include <sim/utils/sim_Misc.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

PID::PID( float kp, float ki, float kd, float min, float max,
          bool reset, float coef ) :
    m_kp ( kp ),
    m_ki ( ki ),
    m_kd ( kd ),

    m_min ( min ),
    m_max ( max ),

    m_error   ( 0.0f ),
    m_error_i ( 0.0f ),
    m_error_d ( 0.0f ),

    m_error_s ( 1 ),

    m_value ( 0.0f ),
    m_delta ( 0.0f ),

    m_coef ( coef ),

    m_reset ( reset )
{}

////////////////////////////////////////////////////////////////////////////////

PID::~PID() {}

////////////////////////////////////////////////////////////////////////////////

void PID::update( float timeStep, float error )
{
    if ( m_reset && Misc::sign( error ) != m_error_s )
    {
        // reseting integral sum of error (anti-windup)
        m_error_i -= m_coef * m_error_i;
        m_error_s = -m_error_s;
    }
    else
    {
        // integration with anti-windup filter
        m_error_i = m_error_i + ( error - m_delta ) * timeStep;
    }

    m_error_d = ( error - m_error ) / timeStep;

    m_error = error;

    float value = m_kp * m_error + m_ki * m_error_i + m_kd * m_error_d;

    // saturation
    m_value = std::max( std::min( value, m_max ), m_min );

    m_delta = value - m_value;
}

////////////////////////////////////////////////////////////////////////////////

void PID::setValue( float value )
{
    m_error   = 0.0f;
    m_error_i = 0.0f;
    m_error_d = 0.0f;

    m_value = value;
    m_delta = 0.0f;
}
