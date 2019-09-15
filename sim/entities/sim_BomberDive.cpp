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

#include <sim/entities/sim_BomberDive.h>

#include <sim/utils/sim_Convert.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

const std::string BomberDive::m_tagName = "bomber_dive";

const float BomberDive::m_dropAltMin = 300.0f;
const float BomberDive::m_dropAltMax = 400.0f;

////////////////////////////////////////////////////////////////////////////////

BomberDive::BomberDive( Affiliation affiliation ) :
    Bomber( affiliation ),

    m_attack ( false )
{}

////////////////////////////////////////////////////////////////////////////////

BomberDive::~BomberDive() {}

////////////////////////////////////////////////////////////////////////////////

int BomberDive::read( const XmlNode &node )
{
    //////////////////////////////////
    int result = Bomber::read( node );
    //////////////////////////////////

    if ( result == SIM_SUCCESS )
    {
        XmlNode nodeData = node.getFirstChildElement( "bomber_dive" );
        readOrdnance( nodeData );

        return SIM_SUCCESS;
    }

    return SIM_FAILURE;
}

////////////////////////////////////////////////////////////////////////////////

void BomberDive::limitTht( float &tht )
{
    if ( m_attack )
    {
        if ( tht < -m_target_tht ) tht = -m_target_tht;
        if ( tht >  m_target_tht ) tht =  m_target_tht;
    }
    else
    {
        ////////////////////////
        Bomber::limitTht( tht );
        ////////////////////////
    }
}

////////////////////////////////////////////////////////////////////////////////

void BomberDive::updateTarget()
{
    ///////////////////////
    Bomber::updateTarget();
    ///////////////////////

    m_attack = false;

    if ( m_engaged )
    {
        if ( m_target_alt > m_dropAltMin )
        {
            float max_range = ( m_airspeed / SIM_GRAVITY_ACC ) * sqrt( 2.0f*SIM_GRAVITY_ACC*m_target_alt );

            if ( m_target_dist < 0.8f*max_range )
            {
                m_attack = true;

                float v_2 = m_airspeed * m_airspeed;
                float num = v_2 - sqrt( v_2*v_2 - SIM_GRAVITY_ACC*(SIM_GRAVITY_ACC*m_target_dist*m_target_dist - 2.0f*m_target_alt*v_2) );
                float den = SIM_GRAVITY_ACC * m_target_dist;

                m_target_tht = atan2( num, den );


                m_destination.first  = m_target_pos;
                m_destination.second = m_speed_min;
            }
        }
        else
        {
            m_engaged = false;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void BomberDive::updateWeapons()
{
    ////////////////////////
    Bomber::updateWeapons();
    ////////////////////////

    if ( m_engaged )
    {
        if ( m_target_alt < m_dropAltMax  )
        {
            m_trigger = true;
        }
    }
    else
    {
        m_trigger = false;
    }

    if ( m_trigger && m_ordnanceIndex < m_ordnance.size() )
    {
        if ( m_time_drop > 0.5f )
        {
            releaseWeapon();
        }
    }
}
