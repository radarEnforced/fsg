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

#include <sim/missions/sim_ObjectiveAirspeed.h>

#include <sim/sim_Ownship.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ObjectiveAirspeed* ObjectiveAirspeed::read( const XmlNode &node )
{
    ObjectiveAirspeed *objective = new ObjectiveAirspeed();

    if ( node.isValid() )
    {
        std::string above = node.getAttribute( "above" );
        std::string below = node.getAttribute( "below" );

        if ( above.length() > 0 && below.length() > 0 )
        {
            objective->m_above = String::toFloat( above );
            objective->m_below = String::toFloat( below );

            return objective;
        }
    }

    if ( objective ) delete objective;
    objective = 0;

    return objective;
}

////////////////////////////////////////////////////////////////////////////////

ObjectiveAirspeed::ObjectiveAirspeed() :
    m_above ( 0.0f ),
    m_below ( 0.0f )
{}

////////////////////////////////////////////////////////////////////////////////

ObjectiveAirspeed::~ObjectiveAirspeed() {}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveAirspeed::update()
{
    Aircraft *aircraft = Ownship::instance()->getAircraft();

    if ( aircraft )
    {
        float airspeed = aircraft->getAirspeed();

        if ( airspeed > m_above && airspeed < m_below )
        {
            m_status = Success;
        }
    }
}
