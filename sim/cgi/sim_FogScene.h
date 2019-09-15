#ifndef SIM_FOGSCENE_H
#define SIM_FOGSCENE_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Fog>
#include <osg/Group>

#include <sim/cgi/sim_Module.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Fog scene module class.
 * <p>This is parent module for all fogged sub-modules.</p>
 */
class FogScene : public Module
{
public:

    static int m_visibility;    ///< [m]

    /** Constructor. */
    FogScene( Module *parent = 0 );

    /** Destructor. */
    virtual ~FogScene();

    /** Updates fog scene module. */
    void update();

private:

    osg::ref_ptr<osg::Fog> m_fog;   ///< fog
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_FOGSCENE_H
