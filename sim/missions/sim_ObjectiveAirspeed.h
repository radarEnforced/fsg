#ifndef SIM_OBJECTIVEAIRSPEED_H
#define SIM_OBJECTIVEAIRSPEED_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/missions/sim_Objective.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Airspeed objective class.
 * <p>Objective is completed if ownship airspeed is in the given range.</p>
 */
class ObjectiveAirspeed : public Objective
{
public:

    /** Reads objective from XML file. */
    static ObjectiveAirspeed* read( const XmlNode &node );

    /** Constructor. */
    ObjectiveAirspeed();

    /** Destructor. */
    virtual ~ObjectiveAirspeed();

    /** Updates objective state. */
    void update();

private:

    float m_above;  ///< [m/s] minimum airspeed
    float m_below;  ///< [m/s] maximum airspeed
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OBJECTIVEAIRSPEED_H
