#ifndef SIM_OBJECTIVEDEFEND_H
#define SIM_OBJECTIVEDEFEND_H

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <sim/missions/sim_Objective.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Defend objective class.
 * <p>Objective is completed if there are at least minimum not destroyed
 * specified units.</p>
 * <p>This objective should be used with another type of objective, because
 * it is assumed to be completed as long as there are minimum not destroyed
 * units so if there were no other objective mission stage would be immediately
 * completed.</p>
 */
class ObjectiveDefend : public Objective
{
public:

    typedef std::vector< UInt32 > UnitsId;

    /** Reads objective from XML file. */
    static ObjectiveDefend* read( const XmlNode &node );

    /** Constructor. */
    ObjectiveDefend();

    /** Destructor. */
    virtual ~ObjectiveDefend();

    /** Updates objective state. */
    void update();

private:

    UnitsId m_unitsId;      ///< IDs of units to be defended

    unsigned int m_minimum; ///< minimum number of units
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OBJECTIVEDEFEND_H
