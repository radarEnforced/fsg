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

#include <sim/sim_Statistics.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Statistics::Statistics() :
    m_activated ( 0 ),
    m_destroyed ( 0 ),

    m_friendsActivated ( 0 ),
    m_friendsDestroyed ( 0 ),
    m_enemiesActivated ( 0 ),
    m_enemiesDestroyed ( 0 ),
    m_ownshipDestroyed ( 0 ),

    m_flightTime ( 0.0f )
{
    reset();
}

////////////////////////////////////////////////////////////////////////////////

Statistics::~Statistics()
{
    reset();
}

////////////////////////////////////////////////////////////////////////////////

void Statistics::reportActivated( Affiliation affiliation )
{
    if ( affiliation == Hostile )
    {
        m_enemiesActivated++;
    }
    else if ( affiliation == Friend )
    {
        m_friendsActivated++;
    }

    m_activated++;
}

////////////////////////////////////////////////////////////////////////////////

void Statistics::reportDestroyed( Affiliation affiliation )
{
    if ( affiliation == Hostile )
    {
        m_enemiesDestroyed++;
    }
    else if ( affiliation == Friend )
    {
        m_friendsDestroyed++;
    }

    m_destroyed++;
}

////////////////////////////////////////////////////////////////////////////////

void Statistics::reset()
{
    m_activated = 0;
    m_destroyed = 0;

    m_friendsActivated = 0;
    m_friendsDestroyed = 0;
    m_enemiesActivated = 0;
    m_enemiesDestroyed = 0;
    m_ownshipDestroyed = 0;

    m_flightTime = 0.0f;
}
