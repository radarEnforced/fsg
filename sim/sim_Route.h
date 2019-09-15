#ifndef SIM_ROUTE_H
#define SIM_ROUTE_H

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <sim/sim_Types.h>

#include <sim/utils/sim_XmlNode.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

typedef std::pair< Vec3, float > WaypointData;  ///< aircraft route waypoint data

////////////////////////////////////////////////////////////////////////////////

/**
 * Aircraft route class.
 * First element is waypoint position, second element is waypoint desired speed.
 */
class Route : public std::vector< WaypointData >
{
public:

    /** Reads route from XML file. */
    static Route* read( const XmlNode &node );

    /** Reads waypoint from XML file.
     * @return FDM_SUCCESS on success or FDM_FAILURE on failure.
     */
    static int read( const XmlNode &node, WaypointData &waypoint );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_ROUTE_H
