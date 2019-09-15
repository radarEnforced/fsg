#ifndef SIM_EXPLOSION_H
#define SIM_EXPLOSION_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Entity.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Explosion effect class. */
class Explosion : public Entity
{
public:

    /** Constructor. */
    Explosion( float scale, Group *parent = 0 );

    /** Destructor. */
    virtual ~Explosion();

private:

    void createExplosionFire( float scale );
    void createExplosionSmoke( float scale );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_EXPLOSION_H
