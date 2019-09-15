#ifndef SIM_UNITGROUND_H
#define SIM_UNITGROUND_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_UnitSurface.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Ground unit base class. */
class UnitGround : public UnitSurface
{
public:

    /** Constructor. */
    UnitGround( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~UnitGround();

    /** Destroys unit. */
    virtual void destroy();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_UNITGROUND_H
