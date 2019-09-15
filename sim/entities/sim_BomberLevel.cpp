#include <sim/entities/sim_BomberLevel.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

const std::string BomberLevel::m_tagName = "bomber_level";

////////////////////////////////////////////////////////////////////////////////

BomberLevel::BomberLevel( Affiliation affiliation ) : Bomber( affiliation ) {}

////////////////////////////////////////////////////////////////////////////////

BomberLevel::~BomberLevel() {}

////////////////////////////////////////////////////////////////////////////////

int BomberLevel::read( const XmlNode &node )
{
    //////////////////////////////////
    int result = Bomber::read( node );
    //////////////////////////////////

    if ( result == SIM_SUCCESS )
    {
        XmlNode nodeData = node.getFirstChildElement( "bomber_level" );
        readOrdnance( nodeData );

        return SIM_SUCCESS;
    }

    return SIM_FAILURE;
}

////////////////////////////////////////////////////////////////////////////////

void BomberLevel::updateWeapons()
{
    ////////////////////////
    Bomber::updateWeapons();
    ////////////////////////

    if ( m_engaged )
    {
        float drop_dist = ( m_airspeed / SIM_GRAVITY_ACC ) * sqrt( 2.0f*SIM_GRAVITY_ACC*m_target_alt );

        if ( fabs( drop_dist - m_target_dist ) < 30.0f )
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
        if ( m_time_drop > 0.2f )
        {
            releaseWeapon();
        }
    }
}
