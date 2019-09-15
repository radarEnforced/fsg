#ifndef SIM_BOMBERLEVEL_H
#define SIM_BOMBERLEVEL_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Bomber.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Level bomber base class. */
class BomberLevel : public Bomber
{
public:

    static const std::string m_tagName; ///<

    /** Constructor. */
    BomberLevel( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~BomberLevel();

    /**
     * Reads bomber data.
     * @return SIM_SUCCESS on success or SIM_FAILURE on failure.
     */
    virtual int read( const XmlNode &node );

protected:

    virtual void updateWeapons();

};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_BOMBERLEVEL_H
