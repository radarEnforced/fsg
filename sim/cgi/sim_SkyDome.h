#ifndef SIM_SKYDOME_H
#define SIM_SKYDOME_H

////////////////////////////////////////////////////////////////////////////////

#ifdef SIM_DESKTOP
#   include <osg/Switch>
#endif

#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>

#include <sim/cgi/sim_Module.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Sky dome module class. */
class SkyDome : public Module
{
public:

    static std::string m_skyDomeFile;   ///< sky dome file
    static float m_sunCoef;

    /** Constructor. */
    SkyDome( Module *parent = 0 );

    /** Destructor. */
    virtual ~SkyDome();

    /** Updates sky dome. */
    void update();

private:

#   ifdef SIM_DESKTOP
    osg::ref_ptr<osg::Switch> m_switch;
#   endif

    osg::ref_ptr<osg::PositionAttitudeTransform> m_patSky;  ///< sky PAT
    osg::ref_ptr<osg::PositionAttitudeTransform> m_patSun;  ///< sun PAT

    void createSky();
    void createSun();

    void createDome( osg::Geode *dome, osg::Texture2D *texture,
                     float radius, bool blend = false );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_SKYDOME_H
