#include <sim/sim_Route.h>

#include <sim/sim_Defs.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Route* Route::read( const XmlNode &node )
{
    Route *route = new Route();

    if ( node.isValid() && route->size() == 0 )
    {
        if ( 0 == String::icompare( node.getName(), "route" ) )
        {
            XmlNode waypointNode = node.getFirstChildElement( "waypoint" );

            int status = SIM_SUCCESS;

            while ( waypointNode.isValid() )
            {
                WaypointData waypoint;

                status = read( waypointNode, waypoint );

                if ( status == SIM_SUCCESS )
                {
                    route->push_back( waypoint );
                }
                else
                {
                    break;
                }

                waypointNode = waypointNode.getNextSiblingElement( "waypoint" );
            }

            if ( status == SIM_SUCCESS && route->size() > 0 )
            {
                return route;
            }
        }
    }

    if ( route ) delete route;
    route = 0;

    return route;
}

////////////////////////////////////////////////////////////////////////////////

int Route::read( const XmlNode &node, WaypointData &waypoint )
{
    if ( node.isValid() )
    {
        if ( 0 == String::icompare( node.getName(), "waypoint" ) )
        {
            XmlNode positionNode = node.getFirstChildElement( "position" );
            XmlNode speedNode    = node.getFirstChildElement( "speed" );

            if ( positionNode.isValid() && speedNode.isValid() )
            {
                Vec3 position;

                if ( SIM_SUCCESS == XmlUtils::read( positionNode, position ) )
                {
                    float speed;

                    if ( SIM_SUCCESS == XmlUtils::read( speedNode, speed ) )
                    {
                        waypoint = WaypointData( position, speed );

                        return SIM_SUCCESS;
                    }
                }
            }
        }
    }

    return SIM_FAILURE;
}