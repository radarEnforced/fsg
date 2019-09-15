#ifndef SIM_WARSHIP_H
#define SIM_WARSHIP_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_UnitMarine.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Warship class. */
class Warship : public UnitMarine
{
public:

    static const std::string m_tagName; ///<

    /** Constructor. */
    Warship( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~Warship();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_WARSHIP_H
