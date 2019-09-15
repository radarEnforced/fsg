#ifndef SIM_BUILDING_H
#define SIM_BUILDING_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_UnitGround.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Building class. */
class Building : public UnitGround
{
public:

    static const std::string m_tagName; ///<

    /** Constructor. */
    Building( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~Building();

protected:

    /** Determines if unit collided with another one. */
    virtual void updateCollisions();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_BUILDING_H
