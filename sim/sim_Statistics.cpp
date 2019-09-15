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
