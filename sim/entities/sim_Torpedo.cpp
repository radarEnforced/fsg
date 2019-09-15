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

#include <sim/entities/sim_Torpedo.h>

#include <sim/entities/sim_Explosion.h>
#include <sim/entities/sim_Entities.h>

#include <sim/sim_Elevation.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Torpedo::Torpedo( UInt32 shooterId, Group *parent ) :
    Munition( 50000, shooterId, 60.0f, parent ),

    m_elevation ( 0.0f )
{}

////////////////////////////////////////////////////////////////////////////////

Torpedo::~Torpedo() {}

////////////////////////////////////////////////////////////////////////////////

void Torpedo::update( double timeStep )
{
    /////////////////////////////
    Munition::update( timeStep );
    /////////////////////////////

    if ( isActive() )
    {
        if ( isTopLevel() )
        {
            if ( m_pos.z() < m_elevation )
            {
                if ( fabs( m_angles.phi() ) < 1.0e-3 )
                {
                    m_omg.y() = -m_angles.tht();
                }
            }
        }
        else
        {
            resetLifeTime();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Torpedo::hit( Unit *target )
{
    ////////////////////////
    Munition::hit( target );
    ////////////////////////

    Explosion *explosion = new Explosion( 15.0f );
    explosion->setPos( m_pos );
}

////////////////////////////////////////////////////////////////////////////////

void Torpedo::updateElevation()
{
    if ( isTopLevel() )
    {
        ////////////////////////////
        Munition::updateElevation();
        ////////////////////////////

        m_elevation = Elevation::instance()->getElevation( m_pos.x(), m_pos.y() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Torpedo::updateVelocity()
{
    if ( isTopLevel() )
    {
        Vec3 acc;

        if ( m_pos.z() > 0.0f )
        {
            if ( m_vel.length() < 100.0f )
            {
                acc = m_att.inverse() * Vec3( 0.0, 0.0, -SIM_GRAVITY_ACC );
            }
        }
        else
        {
            float acc_z = -2.0f * ( m_pos.z() + 2.0f ) - 2.0f * m_vel.z();

            acc = m_att.inverse() * Vec3( 0.0, 0.0, acc_z )
                + Vec3( -m_vel.x() - 25.0f, 0.0, 0.0 );
        }

        m_vel += ( acc - ( m_omg ^ m_vel ) ) * m_timeStep;

        m_omg.x() = -m_angles.phi();
    }
}
