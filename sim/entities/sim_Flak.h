#ifndef SIM_FLAK_H
#define SIM_FLAK_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Bullet.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Flak bullet class. */
class Flak : public Bullet
{
public:

    static const float m_r_limit;   ///< [m] range damage limit
    static const float m_r_limit_2; ///< [m^2] range damage limit squared

    /** Constructor. */
    Flak( UInt32 shooterId, float fuse_time );

    /** Destructor. */
    virtual ~Flak();

    /** Updates tracer. */
    void update( double timeStep );

private:

    float m_fuse_time;  ///< [s]

    bool m_exploded;    ///<

    void hit( Unit *target );

    void rangeDamage();

    void createBurst();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_FLAK_H
