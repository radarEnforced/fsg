#ifndef SIM_MUNITION_H
#define SIM_MUNITION_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Unit.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Munition base class. */
class Munition : public Entity
{
public:

    /** Constructor. */
    Munition( UInt16 dp, UInt32 shooterId, float life_span, Group *parent = 0 );

    /** Destructor. */
    virtual ~Munition();

    /** Loads munition. */
    virtual void load();

    /**
     * @brief Updates munition.
     * <p>Itarates throught top level unit type entities checking intersections
     * of projectile pathway with unit bounding sphere defined as unit radius.
     * If intersection is detected hits unit with specified damage points.</p>
     * @param timeStep
     */
    virtual void update( double timeStep );

    inline UInt32 getShooterId() const { return m_shooterId; }

    /** */
    virtual void setModelFile( const std::string &modelFile );

protected:

    const UInt16 m_dp;  ///< damage points

    UInt32 m_shooterId; ///< shooter ID

    osg::ref_ptr<osg::Node> m_model;    ///< ordnance model node
    std::string m_modelFile;            ///< ordnance model file

    virtual void hit( Unit *target );

    virtual void reportTargetHit( Unit *target );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_MUNITION_H
