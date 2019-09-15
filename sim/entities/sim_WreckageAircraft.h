#ifndef SIM_WRECKAGEAIRCRAFT_H
#define SIM_WRECKAGEAIRCRAFT_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/cgi/sim_Effects.h>
#include <sim/entities/sim_Wreckage.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Aircraft wreckage effect class. */
class WreckageAircraft : public Wreckage
{
public:

    /** Constructor. */
    WreckageAircraft( const std::string &modelFile, const std::string &livery,
                      osgParticle::SmokeEffect *smokeTrail, bool ownship = false );

    /** Destructor. */
    virtual ~WreckageAircraft();

    /** */
    virtual void init( const Vec3 &pos,
                       const Quat &att,
                       const Vec3 &vel,
                       const Vec3 &omg );

    /** Loads aircraft (models, textures, etc.). */
    virtual void load();

    /** Updates effect. */
    virtual void update( double timeStep );

    /** */
    virtual void setState( State state );

private:

    const bool m_ownship;

    osg::ref_ptr<osg::Node> m_model;

    osg::ref_ptr<Effects::Smoke> m_smokeTrail;  ///< smoke trail

    osg::ref_ptr<osg::Switch> m_switchFire;     ///<

    std::string m_livery;       ///< livery path
    std::string m_modelFile;    ///< model file path

    float m_rollRate;           ///< [rad/s] roll rate

    float m_altitude_agl;       ///< [m] altitude above ground level
    float m_elevation;          ///< [m] terrain elevation

    /** */
    void updateElevation();

    /** */
    void updateVelocity();

    /** */
    void createFire();

    /** */
    osg::Node* getModel( const std::string &modelFile );

    /** */
    void loadLivery();

    /** */
    void loadModel();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_WRECKAGEAIRCRAFT_H
