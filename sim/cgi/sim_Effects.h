#ifndef SIM_EFFECTS_H
#define SIM_EFFECTS_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

#include <osgParticle/SmokeEffect>

#include <sim/sim_Base.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Effects class. */
class Effects : public Base
{
public:

    typedef osgParticle::SmokeEffect Smoke;

    /** Creates explosion effect. */
    static osg::Group* createExplosion( float scale );

    /** Creates flames effect. */
    static osg::Group* createFlames( const char *texture );

    /** Creates smoke effect. */
    static osg::Group* createSmoke( float lifeTime = 1.5f,
                                    float size0 = 1.0f, float size1 = 0.2f,
                                    float spread = 1.0f,
                                    float intensity = 1.0f,
                                    float speed = 1.0f );

    /** Creates smoke trail effect. */
    static Smoke* createSmokeTrail();

};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_EFFECTS_H
