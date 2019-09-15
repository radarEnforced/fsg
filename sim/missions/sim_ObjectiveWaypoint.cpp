#include <sim/missions/sim_ObjectiveWaypoint.h>

#include <sim/sim_Ownship.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ObjectiveWaypoint* ObjectiveWaypoint::read( const XmlNode &node )
{
    ObjectiveWaypoint *objective = new ObjectiveWaypoint();

    if ( node.isValid() )
    {
        std::string waypointIndex = node.getAttribute( "index" );

        if ( waypointIndex.length() > 0 )
        {
            int index = String::toInt( waypointIndex );

            if ( index >= 0 )
            {
                objective->m_waypointIndex = index;

                return objective;
            }
        }
    }

    if ( objective ) delete objective;
    objective = 0;

    return objective;
}

////////////////////////////////////////////////////////////////////////////////

ObjectiveWaypoint::ObjectiveWaypoint()
{}

////////////////////////////////////////////////////////////////////////////////

ObjectiveWaypoint::~ObjectiveWaypoint() {}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveWaypoint::update()
{
    Aircraft *aircraft = Ownship::instance()->getAircraft();

    if ( aircraft )
    {
        if ( aircraft->getWaypointIndex() > m_waypointIndex )
        {
            m_status = Success;
        }
    }
}
