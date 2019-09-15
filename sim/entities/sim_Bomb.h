#ifndef SIM_BOMB_H
#define SIM_BOMB_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Munition.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Bomb class. */
class Bomb : public Munition
{
public:

    static const float m_r_limit;   ///< [m] range damage limit
    static const float m_r_limit_2; ///< [m^2] range damage limit squared

    /** Constructor. */
    Bomb( UInt32 shooterId, Group *parent = 0 );

    /** Destructor. */
    virtual ~Bomb();

    /** Updates bomb. */
    virtual void update( double timeStep );

protected:

    float m_elevation;  ///< [m] terrain elevation

    virtual void hit( Unit *target );

    virtual void rangeDamage();

    virtual void updateElevation();
    virtual void updateVelocity();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_BOMB_H
