#ifndef SIM_WRECKAGE_H
#define SIM_WRECKAGE_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Entity.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Wreckage effect base class. */
class Wreckage : public Entity
{
public:

    /** Constructor. */
    Wreckage( osg::Node *model, float life_span = std::numeric_limits< float >::max() );

    /** Destructor. */
    virtual ~Wreckage();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_WRECKAGE_H
