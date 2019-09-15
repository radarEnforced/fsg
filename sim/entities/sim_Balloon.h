#ifndef SIM_BALLOON_H
#define SIM_BALLOON_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_UnitAerial.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Balloon class. */
class Balloon : public UnitAerial
{
public:

    static const std::string m_tagName; ///<

    /** Constructor. */
    Balloon( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~Balloon();

    /** Destroys aircraft. */
    void destroy();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_BALLOON_H
