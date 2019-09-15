#include <sim/entities/sim_WreckageSurface.h>

#ifdef SIM_DESKTOP
#   include <sim/entities/sim_UnitMarine.h>
#endif

#include <sim/cgi/sim_Effects.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

WreckageSurface::WreckageSurface( osg::Node *model , osg::Group *smoke ) :
    Wreckage( model )
{
    osg::ref_ptr<osg::Group> smokeTmp = smoke;

    if ( !smokeTmp.valid() )
    {
        smokeTmp = Effects::createSmoke( 60.0f, 10.0f, 150.0f, 1.0f, 0.04f, 0.5f );
    }

    m_switch->addChild( smokeTmp.get() );

#   ifdef SIM_DESKTOP
    UnitMarine::createReflection( model, m_switch.get() );
#   endif
}

////////////////////////////////////////////////////////////////////////////////

WreckageSurface::~WreckageSurface() {}
