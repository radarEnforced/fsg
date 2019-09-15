#ifndef SIM_OBJECTIVEHEADING_H
#define SIM_OBJECTIVEHEADING_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/missions/sim_Objective.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Heading objective class.
 * <p>Objective is completed if ownship heading is in the given range.</p>
 */
class ObjectiveHeading : public Objective
{
public:

    /** Reads objective from XML file. */
    static ObjectiveHeading* read( const XmlNode &node );

    /** Constructor. */
    ObjectiveHeading();

    /** Destructor. */
    virtual ~ObjectiveHeading();

    /** Updates objective state. */
    void update();

private:

    float m_above;  ///< [rad] minimum heading
    float m_below;  ///< [rad] maximum heading
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OBJECTIVEHEADING_H
