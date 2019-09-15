#ifndef SIM_OBJECTIVEDESTROY_H
#define SIM_OBJECTIVEDESTROY_H

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <sim/missions/sim_Objective.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Destroy objective class.
 * <p>Objective is completed if all specified units are destroyed.</p>
 */
class ObjectiveDestroy : public Objective
{
public:

    typedef std::vector< UInt32 > UnitsId;

    /** Reads objective from XML file. */
    static ObjectiveDestroy* read( const XmlNode &node );

    /** Constructor. */
    ObjectiveDestroy();

    /** Destructor. */
    virtual ~ObjectiveDestroy();

    /** Adds a unit id to be destroyed. */
    void addUnitId( UInt32 unitId );

    /** Updates objective state. */
    void update();

private:

    UnitsId m_unitsId;  ///< IDs of units to be destroyed
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OBJECTIVEDESTROY_H
