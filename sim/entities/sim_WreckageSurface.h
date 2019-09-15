#ifndef SIM_WRECKAGESURFACE_H
#define SIM_WRECKAGESURFACE_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Wreckage.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Surface unit wreckage effect class. */
class WreckageSurface : public Wreckage
{
public:

    /** Constructor. */
    WreckageSurface( osg::Node *model, osg::Group* smoke = 0 );

    /** Destructor. */
    virtual ~WreckageSurface();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_WRECKAGESURFACE_H
