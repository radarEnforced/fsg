#ifndef SIM_BULLET_H
#define SIM_BULLET_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Munition.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Bullet base class. */
class Bullet : public Munition
{
public:

    static const float m_vel_m;     ///< [m/s] muzzle velocity

    /** Constructor. */
    Bullet( UInt16 dp, UInt32 shooterId, float life_span, Group *parent );

    /** Destructor. */
    virtual ~Bullet();

    /** Loads bullet. */
    virtual void load();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_BULLET_H
