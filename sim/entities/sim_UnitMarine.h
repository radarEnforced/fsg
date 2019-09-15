#ifndef SIM_UNITMARINE_H
#define SIM_UNITMARINE_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_UnitSurface.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Marine unit base class. */
class UnitMarine : public UnitSurface
{
public:

#   ifdef SIM_DESKTOP
    static const char m_frag[];     ///<
    static const char m_vert[];     ///<

    static void createReflection( osg::Node *model, osg::Group *parent );
#   endif

    /** Constructor. */
    UnitMarine( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~UnitMarine();

    /** Destroys unit. */
    virtual void destroy();

    /** Loads unit (models, textures, etc.). */
    virtual void load();

    /** Sets unit hit points. */
    virtual void setHP( UInt16 hp );

protected:

    osg::ref_ptr<osg::Group> m_smoke;   ///< damaged unit smoke group
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_UNITMARINE_H
