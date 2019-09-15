#ifndef SIM_KAMIKAZE_H
#define SIM_KAMIKAZE_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/sim_Target.h>

#include <sim/entities/sim_Aircraft.h>
#include <sim/entities/sim_UnitMarine.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Kamikaze class. */
class Kamikaze : public Aircraft
{
public:

    static const std::string m_tagName; ///<

    /** Constructor. */
    Kamikaze( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~Kamikaze();

    /** Overloaded due to extra demage from kamikaze when collide. */
    virtual void collide( Unit *unit );

    /** Updates entity. */
    virtual void update( double timeStep );

    /** Returns aircraft target unit pointer. */
    virtual UnitMarine* getTarget() const;

protected:

    Target< UnitMarine > *m_target;     ///< target

    bool m_engaged;                     ///< specifies if aircraft is engaged into kamikaze attack

    virtual void limitTht( float &tht );

    virtual void updateDestination();
    virtual void updateTarget();

};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_KAMIKAZE_H
