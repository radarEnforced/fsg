#include <sim/sfx/sim_SFX.h>

#ifdef SIM_SFX_OPENSLES
#   include <sim/sfx/sim_EngineOpenSLES.h>
#endif

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

SFX::SFX() :
    m_inited ( false ),
    m_paused ( false ),
    m_rpm ( 0 ),
    m_destroyed ( false ),
    m_ownship_hits ( 0 ),
    m_hit_time ( 0.0f )
{
    m_rpm = new Inertia< float >( 0.5f, 0.85f );
}

////////////////////////////////////////////////////////////////////////////////

SFX::~SFX()
{
    stop();

    if ( m_rpm ) delete m_rpm;
    m_rpm = 0;
}

////////////////////////////////////////////////////////////////////////////////

void SFX::init()
{
    if ( !m_inited )
    {
#       ifdef SIM_SFX_OPENSLES
        EngineOpenSLES::instance()->init();
#       endif

        m_inited = true;
        m_paused = true;
    }
}

////////////////////////////////////////////////////////////////////////////////

void SFX::pause()
{
    m_paused = true;

#   ifdef SIM_SFX_OPENSLES
    EngineOpenSLES::instance()->setPlayerCrash( false );
    EngineOpenSLES::instance()->setPlayerEngine( false );
    EngineOpenSLES::instance()->setPlayerGunfire( false );
    EngineOpenSLES::instance()->setPlayerHeartbeat( false );
    EngineOpenSLES::instance()->setPlayerHit( false );
    EngineOpenSLES::instance()->setPlayerWaypoint( false );
#   endif
}

////////////////////////////////////////////////////////////////////////////////

void SFX::unpause()
{
    m_paused = false;
}

////////////////////////////////////////////////////////////////////////////////

void SFX::stop()
{
    if ( m_inited )
    {
#       ifdef SIM_SFX_OPENSLES
        EngineOpenSLES::instance()->stop();
#       endif

        m_inited = false;
    }
}

////////////////////////////////////////////////////////////////////////////////

void SFX::update()
{
    m_rpm->update( 0.016f, 0.7f + 0.3f * Data::get()->controls.throttle );

#   ifdef SIM_SFX_OPENSLES
    if ( !m_paused )
    {
        if ( !Data::get()->ownship.destroyed )
        {
            // engine
            EngineOpenSLES::instance()->setPlayerEngine( true );
            EngineOpenSLES::instance()->setPlayerEngineRPM( m_rpm->getValue() );

            // gunfire
            EngineOpenSLES::instance()->setPlayerGunfire( Data::get()->ownship.gunfire );

            // hearbeat
            EngineOpenSLES::instance()->setPlayerHeartbeat( Data::get()->ownship.hit_points < 25 );

            // bombs
            EngineOpenSLES::instance()->setPlayerBombs( Data::get()->ownship.bombs_drop < 5.0f );

            // hit
            EngineOpenSLES::instance()->setPlayerHit( Data::get()->ownship.ownship_hit < 0.5f );

            // waypoint
            EngineOpenSLES::instance()->setPlayerWaypoint( Data::get()->ownship.waypoint_time < 1.0 );
        }
        else
        {
            // crash
            if ( !m_destroyed )
            {
                EngineOpenSLES::instance()->setPlayerCrash( true );
            }

            EngineOpenSLES::instance()->setPlayerEngine( false );
            EngineOpenSLES::instance()->setPlayerGunfire( false );
            EngineOpenSLES::instance()->setPlayerHeartbeat( false );
            EngineOpenSLES::instance()->setPlayerHit( false );
            EngineOpenSLES::instance()->setPlayerWaypoint( false );
        }
    }
#   endif

    m_destroyed = Data::get()->ownship.destroyed;
}
