#ifndef SIM_OBJECTIVEWAYPOINT_H
#define SIM_OBJECTIVEWAYPOINT_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/missions/sim_Objective.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Waypoint objective class.
 * <p>This objective is completed when ownship reaches given index waypoint.</p>
 */
class ObjectiveWaypoint : public Objective
{
public:

    /** Reads objective from XML file. */
    static ObjectiveWaypoint* read( const XmlNode &node );

    /** Constructor. */
    ObjectiveWaypoint();

    /** Destructor. */
    virtual ~ObjectiveWaypoint();

    /** Updates objective state. */
    void update();

private:

    UInt32 m_waypointIndex;     ///< waypoint index
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OBJECTIVEWAYPOINT_H
