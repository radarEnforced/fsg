#ifndef SIM_GATES_H
#define SIM_GATES_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osg/Switch>

#include <sim/cgi/sim_Module.h>

#include <sim/entities/sim_Aircraft.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Waypoint gates module class. */
class Gates : public Module
{
public:

    static const float m_distMax;   ///< [m] maximum visibility distance
    static const float m_distScale; ///< [m] minimum scaling distance
    static const float m_size;      ///< [m] waypoint box size

    /** Constructor. */
    Gates( float linesWidth, Module *parent = 0 );

    /** Destructor. */
    virtual ~Gates();

    /** Updates gates module. */
    void update();

private:

    const float m_linesWidth;               ///< [px] lines width

    osg::ref_ptr<osg::Switch> m_switch;     ///< gates visibility switch

    osg::ref_ptr<osg::PositionAttitudeTransform> m_pat0;    ///< current gate PAT
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pat1;    ///< next gate PAT
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pat2;    ///< next next gate PAT

    osg::ref_ptr<osg::Geometry> m_geom0;    ///< current waypoint geometry
    osg::ref_ptr<osg::Geometry> m_geom1;    ///< next waypoint geometry
    osg::ref_ptr<osg::Geometry> m_geom2;    ///< next next waypoint geometry

    osg::Geometry* createGate( osg::Group *parent );

    float updateGate( osg::Geometry *geom, osg::PositionAttitudeTransform *pat,
                      Aircraft *ownship, int number, float coef_prev );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_GATES_H
