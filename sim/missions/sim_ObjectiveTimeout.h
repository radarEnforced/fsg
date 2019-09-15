#ifndef SIM_OBJECTIVETIMEOUT_H
#define SIM_OBJECTIVETIMEOUT_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/missions/sim_Objective.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Timeout objective class.
 * <p>This objective is completed after specified time.</p>
 */
class ObjectiveTimeout : public Objective
{
public:

    /** Reads objective from XML file. */
    static ObjectiveTimeout* read( const XmlNode &node );

    /** Constructor. */
    ObjectiveTimeout();

    /** Destructor. */
    virtual ~ObjectiveTimeout();

    /** Updates objective state. */
    void update();

    void setLimit( float limit );

private:

    bool m_inited;  ///< specifies if objective has been inited

    float m_limit;  ///< [s] time limit
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OBJECTIVETIMEOUT_H
