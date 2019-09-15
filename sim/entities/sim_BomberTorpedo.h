#ifndef SIM_BOMBERTORPEDO_H
#define SIM_BOMBERTORPEDO_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Bomber.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Torpedo bomber class. */
class BomberTorpedo : public Bomber
{
public:

    static const std::string m_tagName; ///<

    static const float m_dropAltMin;    ///< [m]
    static const float m_dropAltMax;    ///< [m]
    static const float m_dropDistMax;   ///< [m]
    static const float m_tanMaxTht;     ///<

    /** Constructor. */
    BomberTorpedo( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~BomberTorpedo();

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

#endif // SIM_BOMBERTORPEDO_H
