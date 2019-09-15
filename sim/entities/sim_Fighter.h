#ifndef SIM_FIGHTER_H
#define SIM_FIGHTER_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/sim_Target.h>

#include <sim/entities/sim_Aircraft.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Fighter aircraft class. */
class Fighter : public Aircraft
{
public:

    static const std::string m_tagName; ///<

    /** Constructor. */
    Fighter( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~Fighter();

    /**
     * Demages fighter.
     * Sets shooter as new target when current target is far.
     * @param dp demage points
     * @param munition munition which hit unit
     */
    virtual void hit( UInt16 dp, const Munition *munition );

    /**
     * Reports hit by fighter's munition.
     * Sets target as a new current target if it's affiliation is opposite.
     * @param target target unit
     */
    virtual void reportTargetHit( Unit *target );

    /** Updates entity. */
    virtual void update( double timeStep );

    /** Returns aircraft target unit pointer. */
    virtual UnitAerial* getTarget() const;

    /**
     * Sets new current target.
     * @param target new current target
     */
    virtual void setTarget( UnitAerial *target );

protected:

    Target< UnitAerial > *m_target;         ///< target

    float m_target_dist;    ///< [m] distance to the current target
    float m_target_bear;    ///< [rad] bearing of the current target
    float m_target_tht;     ///< [rad] relative elevation of the current target
    float m_target_psi;     ///< [rad] relative azimuth of the current target
    float m_target_rad;     ///< [m] target radius

    bool m_engaged;         ///< specifies if aircraft is engaged into combat

    virtual void updateControls();
    virtual void updateDestination();
    virtual void updateTarget();
    virtual void updateTrigger();

};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_FIGHTER_H
