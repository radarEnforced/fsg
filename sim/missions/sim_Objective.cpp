#include <sim/missions/sim_Objective.h>

#include <sim/missions/sim_ObjectiveAirspeed.h>
#include <sim/missions/sim_ObjectiveAltitude.h>
#include <sim/missions/sim_ObjectiveDefend.h>
#include <sim/missions/sim_ObjectiveDestroy.h>
#include <sim/missions/sim_ObjectiveDistance.h>
#include <sim/missions/sim_ObjectiveHeading.h>
#include <sim/missions/sim_ObjectiveTimeout.h>
#include <sim/missions/sim_ObjectiveWaypoint.h>

#include <sim/utils/sim_String.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Objective* Objective::read( const XmlNode &node )
{
    if ( node.isValid() )
    {
        std::string nodeName = node.getName();

        if ( 0 == String::icompare( nodeName, "objective_airspeed" ) )
        {
            return ObjectiveAirspeed::read( node );
        }
        else if ( 0 == String::icompare( nodeName, "objective_altitude" ) )
        {
            return ObjectiveAltitude::read( node );
        }
        else if ( 0 == String::icompare( nodeName, "objective_defend" ) )
        {
            return ObjectiveDefend::read( node );
        }
        else if ( 0 == String::icompare( nodeName, "objective_destroy" ) )
        {
            return ObjectiveDestroy::read( node );
        }
        else if ( 0 == String::icompare( nodeName, "objective_distance" ) )
        {
            return ObjectiveDistance::read( node );
        }
        else if ( 0 == String::icompare( nodeName, "objective_heading" ) )
        {
            return ObjectiveHeading::read( node );
        }
        else if ( 0 == String::icompare( nodeName, "objective_timeout" ) )
        {
            return ObjectiveTimeout::read( node );
        }
        else if ( 0 == String::icompare( nodeName, "objective_waypoint" ) )
        {
            return ObjectiveWaypoint::read( node );
        }
    }

    return 0;
}
