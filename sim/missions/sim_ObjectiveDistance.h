#ifndef SIM_OBJECTIVEDISTANCE_H
#define SIM_OBJECTIVEDISTANCE_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/missions/sim_Objective.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Distance objective class.
 * <p>Objective is completed if ownship distance to the specified unit
 * is less than given limit.</p>
 * <p>This objective should be used with another type of objective, because
 * it is assumed to be completed as long as ownship is closer to the specified
 * unit than given distance so if there were no other objective mission stage
 * would be immediately completed.</p>
 */
class ObjectiveDistance : public Objective
{
public:

    /** Reads objective from XML file. */
    static ObjectiveDistance* read( const XmlNode &node );

    /** Constructor. */
    ObjectiveDistance();

    /** Destructor. */
    virtual ~ObjectiveDistance();

    /** Updates objective state. */
    void update();

private:

    UInt32 m_unitId;    ///< unit ID

    float m_limit;      ///< [m] maximum distance
    float m_limit_2;    ///< [m] maximum distance squared
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OBJECTIVEDISTANCE_H
