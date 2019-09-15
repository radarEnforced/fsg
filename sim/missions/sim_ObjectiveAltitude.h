#ifndef SIM_OBJECTIVEALTITUDE_H
#define SIM_OBJECTIVEALTITUDE_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/missions/sim_Objective.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Altitude objective class.
 * <p>Objective is completed if ownship altitude is in the given range.</p>
 */
class ObjectiveAltitude : public Objective
{
public:

    /** Reads objective from XML file. */
    static ObjectiveAltitude* read( const XmlNode &node );

    /** Constructor. */
    ObjectiveAltitude();

    /** Destructor. */
    virtual ~ObjectiveAltitude();

    /** Updates objective state. */
    void update();

private:

    float m_above;  ///< [m] minimum altitude
    float m_below;  ///< [m] maximum altitude
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OBJECTIVEALTITUDE_H
