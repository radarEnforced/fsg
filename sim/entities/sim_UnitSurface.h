#ifndef SIM_UNITSURFACE_H
#define SIM_UNITSURFACE_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Unit.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Surface (ground or marine) unit base class. */
class UnitSurface : public Unit
{
public:

    /** Constructor. */
    UnitSurface( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~UnitSurface();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_UNITSURFACE_H
