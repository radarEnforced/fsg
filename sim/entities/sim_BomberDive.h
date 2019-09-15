#ifndef SIM_BOMBERDIVE_H
#define SIM_BOMBERDIVE_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Bomber.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Dive bomber class. */
class BomberDive : public Bomber
{
public:

    static const std::string m_tagName; ///<

    static const float m_dropAltMin;    ///< [m]
    static const float m_dropAltMax;    ///< [m]

    /** Constructor. */
    BomberDive( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~BomberDive();

    /**
     * Reads bomber data.
     * @return SIM_SUCCESS on success or SIM_FAILURE on failure.
     */
    virtual int read( const XmlNode &node );

protected:

    bool m_attack;          ///< specifies if aircraft is attacking

    virtual void limitTht( float &tht );

    virtual void updateTarget();
    virtual void updateWeapons();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_BOMBERDIVE_H
