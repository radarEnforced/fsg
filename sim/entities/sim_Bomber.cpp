#include <sim/entities/sim_Bomber.h>

#include <sim/entities/sim_Bomb.h>
#include <sim/entities/sim_Torpedo.h>

#include <sim/utils/sim_Convert.h>
#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Bomber::Bomber( Affiliation affiliation ) :
    Aircraft( affiliation ),

    m_target ( 0 ),

    m_ordnanceIndex ( 0 ),

    m_target_dist ( 0.0f ),
    m_target_alt  ( 0.0f ),
    m_target_tht  ( 0.0f ),
    m_target_psi  ( 0.0f ),

    m_engaged ( false ),
    m_trigger ( false )
{
    m_target = new Target< UnitSurface >( this, ( m_affiliation == Hostile ) ? Friend : Hostile );
}

////////////////////////////////////////////////////////////////////////////////

Bomber::~Bomber()
{
    if ( m_target ) delete m_target;
    m_target = 0;
}

////////////////////////////////////////////////////////////////////////////////

void Bomber::update( double timeStep )
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

UnitSurface* Bomber::getTarget() const
{
    return m_target->getTarget();
}

////////////////////////////////////////////////////////////////////////////////

void Bomber::readOrdnance( const XmlNode &node )
{
    if ( node.isValid() )
    {
        XmlNode nodeOrdnance = node.getFirstChildElement( "bomb" );

        while ( nodeOrdnance.isValid() )
        {
            Bomb *bomb = new Bomb( m_id, this );

            readOrdnance( nodeOrdnance, bomb );
            m_ordnance.push_back( bomb );

            nodeOrdnance = nodeOrdnance.getNextSiblingElement( "bomb" );
        }

        nodeOrdnance = node.getFirstChildElement( "torpedo" );

        while ( nodeOrdnance.isValid() )
        {
            Torpedo *torpedo = new Torpedo( m_id, this );

            readOrdnance( nodeOrdnance, torpedo );
            m_ordnance.push_back( torpedo );

            nodeOrdnance = nodeOrdnance.getNextSiblingElement( "torpedo" );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Bomber::readOrdnance( const XmlNode &node, Munition *ordnance )
{
    if ( node.isValid() && ordnance )
    {
        if ( String::toBool( node.getAttribute( "hidden" ) ) )
        {
            ordnance->makeTopLevel();
            ordnance->setState( Standby );
        }

        ordnance->setModelFile( getPath( node.getAttribute( "model" ) ) );

        XmlNode nodePosition = node.getFirstChildElement( "position" );
        XmlNode nodeAttitude = node.getFirstChildElement( "attitude" );

        if ( nodePosition.isValid() )
        {
            Vec3 position;

            if ( SIM_SUCCESS == XmlUtils::read( nodePosition, position ) )
            {
                ordnance->setPos( position );
            }
        }

        if ( nodeAttitude.isValid() )
        {
            Vec3 attitude;

            if ( SIM_SUCCESS == XmlUtils::read( nodeAttitude, attitude ) )
            {
                Quat quat( Convert::deg2rad( attitude.x() ), osg::X_AXIS,
                           Convert::deg2rad( attitude.y() ), osg::Y_AXIS,
                           Convert::deg2rad( attitude.z() ), osg::Z_AXIS );

                ordnance->setAtt( quat );
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Bomber::releaseWeapon()
{
    m_time_drop = 0.0f;

    m_ordnance[ m_ordnanceIndex ]->setParent( this );
    m_ordnance[ m_ordnanceIndex ]->setState( Active );
    m_ordnance[ m_ordnanceIndex ]->makeTopLevel();

    m_ordnanceIndex++;
}

////////////////////////////////////////////////////////////////////////////////

void Bomber::updateDestination()
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

void Bomber::updateTarget()
{
    UnitSurface *target = m_target->getTarget();

    if ( target && m_ordnanceIndex < m_ordnance.size() )
    {
        m_enroute = false;
        m_wingman = false;
        m_engaged = true;

        m_destValid = true;

        m_target_pos = target->getPos();

        Vec3 dist_enu = m_target_pos - m_pos;
        m_target_dist = sqrt( dist_enu.x()*dist_enu.x() + dist_enu.y()*dist_enu.y() );
        m_target_alt  = -dist_enu.z();

        Vec3 dir_bas = m_att.inverse() * ( dist_enu * ( 1.0/dist_enu.length() ) );
        dir_bas *= 1.0/dir_bas.length();

        m_target_psi = atan2( -dir_bas.y(), -dir_bas.x() );
        m_target_tht = atan2( dir_bas.z(), sqrt( dir_bas.x()*dir_bas.x() + dir_bas.y()*dir_bas.y() ) );

        // mentain level flight
        m_destination.first  = Vec3( m_target_pos.x(), m_target_pos.y(), m_altitude_asl );
        m_destination.second = m_speed_max;
    }
    else
    {
        m_engaged = false;
    }
}
