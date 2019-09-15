#ifndef SIM_TRACER_H
#define SIM_TRACER_H

////////////////////////////////////////////////////////////////////////////////

#include <osgParticle/SmokeTrailEffect>

#include <sim/entities/sim_Bullet.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Tracer bullet class. */
class Tracer : public Bullet
{
public:

    /** Constructor. */
    Tracer( UInt32 shooterId, bool trail = false );

    /** Destructor. */
    virtual ~Tracer();

    /** Loads bullet. */
    virtual void load();

    /** Updates tracer. */
    void update( double timeStep );

private:

//    static UInt8 m_counter_trail;
//    static UInt8 m_quantity;

    float m_elevation;  ///< [m] terrain elevation

//    bool m_trail;       ///< specifies if tracer is a smoke trail
//    unsigned int m_counter_update;
//    osg::ref_ptr<osgParticle::SmokeTrailEffect> m_smokeTrail;

    /** */
    void updateElevation();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_TRACER_H
