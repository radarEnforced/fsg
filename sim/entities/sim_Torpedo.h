#ifndef SIM_TORPEDO_H
#define SIM_TORPEDO_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Munition.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Torpedo class. */
class Torpedo : public Munition
{
public:

    /** Constructor. */
    Torpedo( UInt32 shooterId, Group *parent = 0 );

    /** Destructor. */
    virtual ~Torpedo();

    /** Updates torpedo. */
    virtual void update( double timeStep );

protected:

    float m_elevation;  ///< [m] terrain elevation

    virtual void hit( Unit *target );

    virtual void updateElevation();
    virtual void updateVelocity();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_TORPEDO_H
