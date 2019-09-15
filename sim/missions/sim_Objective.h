#ifndef SIM_OBJECTIVE_H
#define SIM_OBJECTIVE_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/sim_Base.h>

#include <sim/utils/sim_XmlNode.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Mission objective base class. */
class Objective : public Base
{
public:

    /** Reads objective from XML file. */
    static Objective* read( const XmlNode &node );

    /** Constructor. */
    Objective() : m_status( Pending ) {}

    /** Destructor. */
    virtual ~Objective() {}

    /** Updates objective state. */
    virtual void update() = 0;

    inline Status getStatus() const { return m_status; }

protected:

    Status m_status;    ///< objective status
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OBJECTIVE_H
