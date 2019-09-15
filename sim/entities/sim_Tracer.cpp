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

#include <sim/entities/sim_Tracer.h>

#include <sim/cgi/sim_Models.h>
#include <sim/entities/sim_Entities.h>
#include <sim/sim_Elevation.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

//UInt8 Tracer::m_counter_trail = 0;
//UInt8 Tracer::m_quantity      = 0;

////////////////////////////////////////////////////////////////////////////////

Tracer::Tracer( UInt32 shooterId, bool trail ) :
    Bullet( 25, shooterId, 5.0f, 0 ),
    m_elevation ( 0.0f )
//    m_trail ( false ),
//    m_counter_update ( 0 )
{
    load();

//    if ( trail ) m_counter_trail++;
}

////////////////////////////////////////////////////////////////////////////////

Tracer::~Tracer()
{
//    if ( m_trail && m_quantity > 0 )
//    {
//        m_quantity--;
//    }
}

////////////////////////////////////////////////////////////////////////////////

void Tracer::load()
{
    if ( m_switch->getNumChildren() > 0 )
    {
        m_switch->removeChildren( 0, m_switch->getNumChildren() );
    }

    m_model = Models::getTracer();

    if ( m_model.valid() )
    {
        m_switch->addChild( m_model.get() );
    }

//    if ( trail && m_quantity < 50 && m_counter_trail % 5 == 0 )
//    {
//        m_trail = true;

//        m_counter_trail = 0;

//        m_smokeTrail = new osgParticle::SmokeTrailEffect();
//        m_root->addChild( m_smokeTrail.get() );

//        m_smokeTrail->setTextureFileName( getPath( "textures/smoke_trail.rgb" ) );
//        m_smokeTrail->setScale( 0.2f );
//        m_smokeTrail->setEmitterDuration( 1.0f );
//        m_smokeTrail->setIntensity( 0.01f );
//        m_smokeTrail->setUseLocalParticleSystem( true );
//        m_smokeTrail->setParticleDuration( 1.0f );

//        osg::ref_ptr<osg::StateSet> stateSet = m_smokeTrail->getOrCreateStateSet();
//        stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
//        stateSet->setRenderBinDetails( SIM_DEPTH_SORTED_BIN_TRAIL, "DepthSortedBin" );

//        m_quantity++;
//    }
//    else
//    {
//        m_trail = false;
//    }
}

////////////////////////////////////////////////////////////////////////////////

void Tracer::update( double timeStep )
{
    /////////////////////////////
    Munition::update( timeStep );
    /////////////////////////////

    if ( m_pos.z() < m_elevation )
    {
        setState( Inactive );
    }

//    if ( m_trail && m_smokeTrail.valid() )
//    {
//        if ( m_counter_update % ( m_counter_update <= 5 ? 5 : 20 ) == 0 )
//        {
//            if ( m_life_time < 1.5f )
//            {
//                m_smokeTrail->setPosition( m_pos );
//            }
//            else
//            {
//                m_root->removeChild( m_smokeTrail.get() );
//                m_smokeTrail.release();
//            }
//        }

//        m_counter_update++;
//    }
}

////////////////////////////////////////////////////////////////////////////////

void Tracer::updateElevation()
{
    if ( isTopLevel() )
    {
        ////////////////////////////
        Munition::updateElevation();
        ////////////////////////////

        m_elevation = Elevation::instance()->getElevation( m_pos.x(), m_pos.y() );
    }
}
