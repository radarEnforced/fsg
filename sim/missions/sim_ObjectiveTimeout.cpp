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

#include <sim/missions/sim_ObjectiveTimeout.h>

#include <sim/sim_Ownship.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ObjectiveTimeout* ObjectiveTimeout::read( const XmlNode &node )
{
    ObjectiveTimeout *objective = new ObjectiveTimeout();

    if ( node.isValid() )
    {
        std::string limit = node.getAttribute( "limit" );

        if ( limit.length() > 0 )
        {
            objective->m_limit = String::toFloat( limit );

            return objective;
        }
    }

    if ( objective ) delete objective;
    objective = 0;

    return objective;
}

////////////////////////////////////////////////////////////////////////////////

ObjectiveTimeout::ObjectiveTimeout() :
    m_inited ( false ),
    m_limit ( 0.0f )
{}

////////////////////////////////////////////////////////////////////////////////

ObjectiveTimeout::~ObjectiveTimeout() {}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveTimeout::update()
{
    if ( !m_inited )
    {
        m_limit += Data::get()->mission.real_time;
        m_inited = true;
    }

    if ( Data::get()->mission.real_time > m_limit )
    {
        m_status = Success;
    }
}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveTimeout::setLimit( float limit )
{
    m_limit = limit;
}
