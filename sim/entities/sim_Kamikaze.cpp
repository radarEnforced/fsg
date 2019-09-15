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

#include <sim/entities/sim_Kamikaze.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

const std::string Kamikaze::m_tagName = "kamikaze";

////////////////////////////////////////////////////////////////////////////////

Kamikaze::Kamikaze( Affiliation affiliation ) :
    Aircraft( affiliation ),

    m_target ( 0 ),
    m_engaged ( false )
{
    m_target = new Target< UnitMarine >( this, ( m_affiliation == Hostile ) ? Friend : Hostile );
}

////////////////////////////////////////////////////////////////////////////////

Kamikaze::~Kamikaze()
{
    if ( m_target ) delete m_target;
    m_target = 0;
}

////////////////////////////////////////////////////////////////////////////////

void Kamikaze::collide( Unit *unit )
{
    unit->damage( 65535 );
}

////////////////////////////////////////////////////////////////////////////////

void Kamikaze::update( double timeStep )
{
    if ( isActive() ) m_target->update();

    /////////////////////////////
    Aircraft::update( timeStep );
    /////////////////////////////

    if ( isActive() )
    {
        if ( !m_target->getTarget() )
        {
            m_target->findForward( M_PI_2 );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

UnitMarine *Kamikaze::getTarget() const
{
    return m_target->getTarget();
}

////////////////////////////////////////////////////////////////////////////////

void Kamikaze::limitTht( float &tht )
{
    if ( m_engaged )
    {
        if ( tht < -SIM_AIRCRAFT_MAX_THT ) tht = -SIM_AIRCRAFT_MAX_THT;
        if ( tht >  SIM_AIRCRAFT_MAX_THT ) tht =  SIM_AIRCRAFT_MAX_THT;
    }
    else
    {
        //////////////////////////
        Aircraft::limitTht( tht );
        //////////////////////////
    }
}

////////////////////////////////////////////////////////////////////////////////

void Kamikaze::updateDestination()
{
    updateTarget();

    if ( !m_engaged )
    {
        if ( m_route.size() > 0 )
        {
            if ( !m_enroute || m_engaged )
            {
                m_destination = m_route[ m_waypointIndex ];
                m_destValid = true;
            }
        }
        else
        {
            m_destValid = false;
        }

        m_enroute = true;
        m_wingman = m_leaderValid;
        m_engaged = false;
    }

    //////////////////////////////
    Aircraft::updateDestination();
    //////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////

void Kamikaze::updateTarget()
{
    UnitMarine *target = m_target->getTarget();

    if ( target )
    {
        m_enroute = false;
        m_wingman = false;
        m_engaged = true;

        m_destValid = true;

        Vec3 pos_enu = target->getPos();
        pos_enu.z() = 5.0f;

        m_destination.first  = pos_enu;
        m_destination.second = m_speed_max;
    }
    else
    {
        m_engaged = false;
    }
}

